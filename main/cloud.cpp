#include "cloud.h"

// system includes
#include <optional>

// esp-idf includes
#include <esp_log.h>

// 3rdparty lib includes
#include <ArduinoJson.h>
#include <esphttpdutils.h>
#include <espwifistack.h>
#include <fmt/core.h>
#include <tftinstance.h>
#include <tickchrono.h>
#include <wrappers/websocket_client.h>

// local includes
#include "bobbyerrorhandler.h"
#include "globals.h"
#include "newsettings.h"
#include "utils.h"

using namespace std::chrono_literals;

namespace {
constexpr const char * const TAG = "BOBBYCLOUD";
} // namespace


espcpputils::websocket_client cloudClient;
bool cloudStarted{};
espchrono::millis_clock::time_point lastCreateTry;
espchrono::millis_clock::time_point lastStartTry;
std::string cloudBuffer;

std::optional<espchrono::millis_clock::time_point> lastCloudCollect;
std::optional<espchrono::millis_clock::time_point> lastCloudSend;

bool hasAnnouncedItself{};

void initCloud()
{
    if (configs.cloudSettings.cloudEnabled.value() &&
        !configs.cloudUrl.value().empty() && configs.cloudSettings.cloudMode.value() != CloudMode::INACTIVE && wifi_stack::get_sta_status() == wifi_stack::WiFiStaStatus::CONNECTED)
    {
        createCloud();
        if (!cloudClient)
            return;

        startCloud();
    }
}

void updateCloud()
{
    if (!configs.feature.cloud.isEnabled.value())
        return;

    const auto now = espchrono::millis_clock::now();

    if (configs.cloudSettings.cloudMode.value() == CloudMode::STATISTICS || configs.cloudSettings.cloudMode.value() == CloudMode::STATISTICS_AND_REMOTE_DISPLAY)
    {
        if (!lastCloudCollect || now - *lastCloudCollect >= std::chrono::milliseconds{
                configs.boardcomputerHardware.timersSettings.cloudCollectRate.value()}) {
            cloudCollect();

            lastCloudCollect = now;
        }
    }

    if (!lastCloudSend || now - *lastCloudSend >= 1000ms/configs.boardcomputerHardware.timersSettings.cloudSendRate.value())
    {
        cloudSend();

        lastCloudSend = now;
    }
}

void cloudCollect()
{
    if (!cloudClient)
    {
        cloudBuffer.clear();
        return;
    }

    if (!cloudStarted)
    {
        cloudBuffer.clear();
        return;
    }

    if (!cloudClient.is_connected())
    {
        cloudBuffer.clear();
        return;
    }

    if (configs.cloudSettings.cloudMode.value == CloudMode::STATISTICS || configs.cloudSettings.cloudMode.value == CloudMode::STATISTICS_AND_REMOTE_DISPLAY)
    {
        if (cloudBuffer.empty())
            cloudBuffer = '[';
        else
            cloudBuffer += ',';

        cloudBuffer += fmt::format("[{},{},{}",
                          std::chrono::floor<std::chrono::milliseconds>(espchrono::millis_clock::now().time_since_epoch()).count(),
                          std::chrono::floor<std::chrono::milliseconds>(espchrono::utc_clock::now().time_since_epoch()).count(),
                          heap_caps_get_free_size(MALLOC_CAP_INTERNAL|MALLOC_CAP_8BIT));
        if (wifi_stack::get_sta_status() == wifi_stack::WiFiStaStatus::CONNECTED)
        {
            if (const auto &result = wifi_stack::get_sta_ap_info(); result)
                cloudBuffer += fmt::format(",{}", result->rssi);
            else
                cloudBuffer += ",null";
        }
        else
            cloudBuffer += ",null";

        if (raw_gas)
            cloudBuffer += fmt::format(",{}", *raw_gas);
        else
            cloudBuffer += ",null";

        if (raw_brems)
            cloudBuffer += fmt::format(",{}", *raw_brems);
        else
            cloudBuffer += ",null";

        if (gas)
            cloudBuffer += fmt::format(",{:.1f}", *gas);
        else
            cloudBuffer += ",null";

        if (brems)
            cloudBuffer += fmt::format(",{:.1f}", *brems);
        else
            cloudBuffer += ",null";

        constexpr const auto addController = [](const Controller &controller){
            if (!controller.feedbackValid)
            {
                cloudBuffer += ",null";
                return;
            }

            cloudBuffer += fmt::format(",[{:.02f},{:.02f}",
                               controller.getCalibratedVoltage(),
                               fixBoardTemp(controller.feedback.boardTemp));

            constexpr const auto addMotor = [](const bobbycar::protocol::serial::MotorState &command,
                                               const bobbycar::protocol::serial::MotorFeedback &feedback,
                                               bool invert){
                cloudBuffer += fmt::format(",[{},{:.2f},{:.2f},{}]",
                                   command.pwm * (invert?-1:1),
                                   convertToKmh(feedback.speed) * (invert?-1:1),
                                   fixCurrent(feedback.dcLink),
                                   feedback.error);
            };

            addMotor(controller.command.left, controller.feedback.left, controller.invertLeft);
            addMotor(controller.command.right, controller.feedback.right, controller.invertRight);

            cloudBuffer += ']';
        };

        addController(controllers.front);
        addController(controllers.back);

        //cloudBuffer += fmt::format("", );

        cloudBuffer += "]";
    }
}

void cloudSend()
{
    if (configs.cloudSettings.cloudEnabled.value() &&
        !configs.cloudUrl.value().empty() && (configs.cloudSettings.cloudMode.value() == CloudMode::STATISTICS || configs.cloudSettings.cloudMode.value() == CloudMode::STATISTICS_AND_REMOTE_DISPLAY) || ((configs.cloudSettings.cloudMode.value() == CloudMode::REMOTE_DISPLAY || configs.cloudSettings.cloudMode.value() == CloudMode::STATISTICS_AND_REMOTE_DISPLAY) && !hasAnnouncedItself))
    {
        if (!cloudClient)
        {
            if (espchrono::ago(lastCreateTry) < 10s)
                return;
            createCloud();
        }
        if (!cloudClient)
            return;

        if (!cloudStarted)
        {
            if (espchrono::ago(lastStartTry) < 10s)
                return;

            if (wifi_stack::get_sta_status() != wifi_stack::WiFiStaStatus::CONNECTED)
                return;

            startCloud();
        }

        if (!cloudStarted)
            return;

        if (!cloudClient.is_connected())
            return;

        if (cloudBuffer.empty() && hasAnnouncedItself)
            return;

        cloudBuffer += ']';

        const auto timeout = std::chrono::ceil<espcpputils::ticks>(espchrono::milliseconds32{configs.cloudSettings.cloudTransmitTimeout.value()}).count();

        if (!hasAnnouncedItself)
        {
            std::string helloWorld = getLoginMessage();
            ESP_LOGW(TAG, "=====> %s", helloWorld.c_str());
            const auto written_helloWorld = cloudClient.send_text(helloWorld, timeout);
            if (written_helloWorld == helloWorld.size())
                hasAnnouncedItself = true;
        }

        const auto written = cloudClient.send_text(cloudBuffer, timeout);

        if (written < 0)
        {
            ESP_LOGE("BOBBY", "cloudClient.send_text() failed with %i", written);
        }
        else if (written != cloudBuffer.size())
        {
            ESP_LOGE("BOBBY", "websocket sent size mismatch, sent=%i, expected=%i", written, cloudBuffer.size());
        }

        cloudBuffer.clear();
    }
    else if (cloudClient && !configs.cloudSettings.cloudEnabled.value)
    {
        destroyCloud();
    }
    else if(!cloudClient || !cloudStarted)
    {
        initCloud();
    }
}

std::string getLoginMessage()
{
    using namespace espgui;
    return fmt::format(R"({{"type": "hello", "name": "{}", "res": "{}x{}", "pass": "{}", "key": "{}"}})",
                       configs.otaUsername.value(), tft.width(), tft.height(), configs.webserverPassword.value(), configs.cloudSettings.cloudKey.value());
}


void cloudSendDisplay(std::string_view data)
{
    if (configs.cloudSettings.cloudEnabled.value &&
        !configs.cloudUrl.value.empty() && configs.cloudSettings.cloudMode.value != CloudMode::INACTIVE)
    {
        if (!cloudClient)
        {
            if (espchrono::ago(lastCreateTry) < 10s)
                return;
            createCloud();
        }
        if (!cloudClient)
            return;

        if (!cloudStarted)
        {
            if (espchrono::ago(lastStartTry) < 10s)
                return;

            if (wifi_stack::get_sta_status() != wifi_stack::WiFiStaStatus::CONNECTED)
                return;

            startCloud();
        }
        if (!cloudStarted)
            return;

        if (!cloudClient.is_connected())
            return;

        auto timeout = std::chrono::ceil<espcpputils::ticks>(espchrono::milliseconds32{configs.cloudSettings.cloudTransmitTimeout.value}).count();
        int written;

        if (hasAnnouncedItself)
            written = cloudClient.send_text(data, timeout);
        else
            return;
        ESP_LOGW(TAG, "%s", fmt::format("{}", data).c_str());

        if (written < 0)
        {
            ESP_LOGE("BOBBY", "cloudClient.send_text() failed with %i", written);
            hasAnnouncedItself = false;
        }
        else if (written != data.size())
        {
            ESP_LOGE("BOBBY", "websocket sent size mismatch, sent=%i, expected=%i", written, data.size());
        }
    }
    else if (cloudClient && !configs.cloudSettings.cloudEnabled.value)
    {
        destroyCloud();
    }
}

void createCloud()
{
    hasAnnouncedItself = false;
    ESP_LOGI("BOBBY", "called");

    if (cloudClient)
    {
        ESP_LOGE(TAG, "cloud client already created");
        return;
    }

    lastCreateTry = espchrono::millis_clock::now();

    const esp_websocket_client_config_t config = {
        .uri = configs.cloudUrl.value().c_str(),
    };

    cloudClient = espcpputils::websocket_client{&config};

    cloudClient.register_events(WEBSOCKET_EVENT_CONNECTED, [](void* event_handler_arg, esp_event_base_t event_base, int32_t event_id, void* event_data){
        hasAnnouncedItself = false;
    }, nullptr);

    cloudClient.register_events(WEBSOCKET_EVENT_DATA, [](void* event_handler_arg, esp_event_base_t event_base, int32_t event_id, void* event_data){
        using namespace ArduinoJson;
        auto data = static_cast<esp_websocket_event_data_t*>(event_data);

        if (data->op_code != 1) // text
            return;

        StaticJsonDocument<768> doc;
        if (const auto err = deserializeJson(doc, data->data_ptr, data->data_len); err)
        {
            ESP_LOGE(TAG, "deserializeJson() failed with %s", err.c_str());
            return;
        }

        const std::string type = doc["type"];
        if (type == "popup")
        {
            std::string text = doc["msg"];
            std::string id = doc["id"];
            ESP_LOGI(TAG, "popup: %s, id: %s", text.c_str(), id.c_str());
            BobbyErrorHandler{}.errorOccured(std::move(text));

            if (id.empty())
                return;

            auto timeout = std::chrono::ceil<espcpputils::ticks>(espchrono::milliseconds32{configs.cloudSettings.cloudTransmitTimeout.value}).count();
            const auto message = fmt::format(R"({{"type":"response","id":"{}"}})", id);
            ESP_LOGI(TAG, "sending response: %s", message.c_str());
            cloudClient.send_text(message, timeout);
            return;
        }
    }, nullptr);

    if (!cloudClient)
    {
        ESP_LOGE(TAG, "websocket could not be constructed");
        return;
    }

    ESP_LOGI("BOBBY", "cloud client created");
}

void startCloud()
{
    hasAnnouncedItself = false;
    ESP_LOGI("BOBBY", "called");

    if (!cloudClient)
    {
        ESP_LOGE(TAG, "cloud client not created");
        return;
    }

    if (cloudStarted)
    {
        ESP_LOGE(TAG, "cloud client already started");
        return;
    }

    lastStartTry = espchrono::millis_clock::now();

    const auto result = cloudClient.start();
    ESP_LOG_LEVEL_LOCAL((result == ESP_OK ? ESP_LOG_INFO : ESP_LOG_ERROR), "BOBBY", "cloudClient.start() returned: %s", esp_err_to_name(result));

    if (result == ESP_OK)
        cloudStarted = true;
}

void destroyCloud()
{
    hasAnnouncedItself = false;
    ESP_LOGI("BOBBY", "called");

    if (!cloudClient)
    {
        ESP_LOGE(TAG, "cloud client not created");
        return;
    }

    cloudClient = {};
    cloudStarted = false;
}
