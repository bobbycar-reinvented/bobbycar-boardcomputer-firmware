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
#include <numberparsing.h>
#include <tftinstance.h>
#include <tickchrono.h>
#include <wrappers/websocket_client.h>

// local includes
#include "bobbyerrorhandler.h"
#include "globals.h"
#include "newsettings.h"
#include "utils.h"

using namespace std::chrono_literals;

espcpputils::websocket_client cloudClient;
bool cloudStarted{};
espchrono::millis_clock::time_point lastCreateTry;
espchrono::millis_clock::time_point lastStartTry;
std::string cloudBuffer;

std::optional<espchrono::millis_clock::time_point> lastCloudCollect;
std::optional<espchrono::millis_clock::time_point> lastCloudSend;
std::optional<espchrono::millis_clock::time_point> lastHeartbeat;

bool hasAnnouncedItself{};

namespace {
constexpr const char * const TAG = "BOBBYCLOUD";
constexpr const auto json_document_size = 256;
StaticJsonDocument<json_document_size> doc;

template<class T>
struct is_duration : std::false_type {};

template<class Rep, class Period>
struct is_duration<std::chrono::duration<Rep, Period>> : std::true_type {};

template <typename _Tp>
inline constexpr bool is_duration_v = is_duration<_Tp>::value;

template<typename T>
typename std::enable_if<
        !std::is_same_v<T, bool> &&
        !std::is_integral_v<T> &&
        !is_duration_v<T> &&
        !std::is_same_v<T, std::string> &&
        !std::is_same_v<T, wifi_stack::ip_address_t> &&
        !std::is_same_v<T, wifi_stack::mac_t> &&
        !std::is_same_v<T, std::optional<wifi_stack::mac_t>> &&
        !std::is_same_v<T, wifi_auth_mode_t> &&
        !std::is_same_v<T, sntp_sync_mode_t> &&
        !std::is_same_v<T, espchrono::DayLightSavingMode> &&
        !std::is_same_v<T, OtaAnimationModes> &&
        !std::is_same_v<T, LedstripAnimation> &&
        !std::is_same_v<T, HandbremseMode> &&
        !std::is_same_v<T, CloudMode> &&
        !std::is_same_v<T, BobbyQuickActions>
        , void>::type
toArduinoJson(std::string_view key, T value, StaticJsonDocument<json_document_size> &doc)
{
    doc[key.data()] = nullptr;
}

template<typename T>
typename std::enable_if<
        std::is_same_v<T, bool>
        , void>::type
toArduinoJson(std::string_view key, T value, StaticJsonDocument<json_document_size> &doc)
{
    doc[key.data()] = value;
}

template<typename T>
typename std::enable_if<
        !std::is_same_v<T, bool> &&
        std::is_integral_v<T>
        , void>::type
toArduinoJson(std::string_view key, T value, StaticJsonDocument<json_document_size> &doc)
{
    doc[key.data()] = value;
}

template<typename T>
typename std::enable_if<
        is_duration_v<T>
        , void>::type
toArduinoJson(std::string_view key, T value, StaticJsonDocument<json_document_size> &doc)
{
    doc[key.data()] = value.count();
}

template<typename T>
typename std::enable_if<
        std::is_same_v<T, std::string>
        , void>::type
toArduinoJson(std::string_view key, T value, StaticJsonDocument<json_document_size> &doc)
{
    doc[key.data()] = value.data();
}

template<typename T>
typename std::enable_if<
        std::is_same_v<T, wifi_stack::ip_address_t>
        , void>::type
toArduinoJson(std::string_view key, T value, StaticJsonDocument<json_document_size> &doc)
{
    doc[key.data()] = wifi_stack::toString(value);
}

template<typename T>
typename std::enable_if<
        std::is_same_v<T, wifi_stack::mac_t>
        , void>::type
toArduinoJson(std::string_view key, T value, StaticJsonDocument<json_document_size> &doc)
{
    doc[key.data()] = wifi_stack::toString(value);
}

template<typename T>
typename std::enable_if<
        std::is_same_v<T, std::optional<wifi_stack::mac_t>>
        , void>::type
toArduinoJson(std::string_view key, T value, StaticJsonDocument<json_document_size> &doc)
{
    doc[key.data()] = value ? wifi_stack::toString(*value) : std::string{};
}

template<typename T>
typename std::enable_if<
        std::is_same_v<T, wifi_auth_mode_t>
        , void>::type
toArduinoJson(std::string_view key, T value, StaticJsonDocument<json_document_size> &doc)
{
    doc[key.data()] = wifi_stack::toString(value);
}

template<typename T>
typename std::enable_if<
        std::is_same_v<T, sntp_sync_mode_t>
        , void>::type
toArduinoJson(std::string_view key, T value, StaticJsonDocument<json_document_size> &doc)
{
    doc[key.data()] = std::to_underlying(value);
}

template<typename T>
typename std::enable_if<
        std::is_same_v<T, espchrono::DayLightSavingMode>
        , void>::type
toArduinoJson(std::string_view key, T value, StaticJsonDocument<json_document_size> &doc)
{
    doc[key.data()] = std::to_underlying(value);
}

template<typename T>
typename std::enable_if<
        std::is_same_v<T, OtaAnimationModes>
        , void>::type
toArduinoJson(std::string_view key, T value, StaticJsonDocument<json_document_size> &doc)
{
    doc[key.data()] = std::to_underlying(value);
}

template<typename T>
typename std::enable_if<
        std::is_same_v<T, LedstripAnimation>
        , void>::type
toArduinoJson(std::string_view key, T value, StaticJsonDocument<json_document_size> &doc)
{
    doc[key.data()] = std::to_underlying(value);
}

template<typename T>
typename std::enable_if<
        std::is_same_v<T, HandbremseMode>
        , void>::type
toArduinoJson(std::string_view key, T value, StaticJsonDocument<json_document_size> &doc)
{
    doc[key.data()] = std::to_underlying(value);
}

template<typename T>
typename std::enable_if<
        std::is_same_v<T, BobbyQuickActions>
        , void>::type
toArduinoJson(std::string_view key, T value, StaticJsonDocument<json_document_size> &doc)
{
    doc[key.data()] = std::to_underlying(value);
}

template<typename T>
typename std::enable_if<
        std::is_same_v<T, CloudMode>
        , void>::type
toArduinoJson(std::string_view key, T value, StaticJsonDocument<json_document_size> &doc)
{
    doc[key.data()] = std::to_underlying(value);
}


template<typename T>
typename std::enable_if<
        !std::is_same_v<T, bool> &&
        !std::is_integral_v<T> &&
        !std::is_same_v<T, std::string> &&
        !std::is_same_v<T, wifi_stack::ip_address_t> &&
        !std::is_same_v<T, wifi_stack::mac_t> &&
        !std::is_same_v<T, std::optional<wifi_stack::mac_t>> &&
        !std::is_same_v<T, wifi_auth_mode_t> &&
        !std::is_same_v<T, sntp_sync_mode_t> &&
        !std::is_same_v<T, espchrono::DayLightSavingMode> &&
        !std::is_same_v<T, OtaAnimationModes> &&
        !std::is_same_v<T, LedstripAnimation> &&
        !std::is_same_v<T, HandbremseMode> &&
        !std::is_same_v<T, CloudMode> &&
        !std::is_same_v<T, BobbyQuickActions>
        , tl::expected<void, std::string>>::type
set_config(ConfigWrapper<T> &config, std::string_view newValue)
{
    return tl::make_unexpected("Unsupported config type");
}

template<typename T>
typename std::enable_if<
        std::is_same_v<T, bool>
        , tl::expected<void, std::string>>::type
set_config(ConfigWrapper<T> &config, std::string_view newValue)
{
    if (cpputils::is_in(newValue, "true", "false"))
        return configs.write_config(config, newValue == "true");
    else
        return tl::make_unexpected(fmt::format("only true and false allowed, not {}", newValue));
}

template<typename T>
typename std::enable_if<
        !std::is_same_v<T, bool> &&
        std::is_integral_v<T>
        , tl::expected<void, std::string>>::type
set_config(ConfigWrapper<T> &config, std::string_view newValue)
{
    if (auto parsed = cpputils::fromString<T>(newValue))
        return configs.write_config(config, *parsed);
    else
        return tl::make_unexpected(fmt::format("could not parse {}", newValue));
}

template<typename T>
typename std::enable_if<
        std::is_same_v<T, std::string>
        , tl::expected<void, std::string>>::type
set_config(ConfigWrapper<T> &config, std::string_view newValue)
{
    return configs.write_config(config, std::string{newValue});
}

template<typename T>
typename std::enable_if<
        std::is_same_v<T, wifi_stack::ip_address_t>
        , tl::expected<void, std::string>>::type
set_config(ConfigWrapper<T> &config, std::string_view newValue)
{
    if (const auto parsed = wifi_stack::fromString<wifi_stack::ip_address_t>(newValue); parsed)
        return configs.write_config(config, *parsed);
    else
        return tl::make_unexpected(parsed.error());
}

template<typename T>
typename std::enable_if<
        std::is_same_v<T, wifi_stack::mac_t>
        , tl::expected<void, std::string>>::type
set_config(ConfigWrapper<T> &config, std::string_view newValue)
{
    if (const auto parsed = wifi_stack::fromString<wifi_stack::mac_t>(newValue); parsed)
        return configs.write_config(config, *parsed);
    else
        return tl::make_unexpected(parsed.error());
}

template<typename T>
typename std::enable_if<
        std::is_same_v<T, std::optional<wifi_stack::mac_t>>
        , tl::expected<void, std::string>>::type
set_config(ConfigWrapper<T> &config, std::string_view newValue)
{
    if (newValue.empty())
        return configs.write_config(config, std::nullopt);
    else if (const auto parsed = wifi_stack::fromString<wifi_stack::mac_t>(newValue); parsed)
        return configs.write_config(config, *parsed);
    else
        return tl::make_unexpected(parsed.error());
}

template<typename T>
typename std::enable_if<
        std::is_same_v<T, wifi_auth_mode_t> ||
        std::is_same_v<T, sntp_sync_mode_t> ||
        std::is_same_v<T, espchrono::DayLightSavingMode> ||
        std::is_same_v<T, OtaAnimationModes> ||
        std::is_same_v<T, LedstripAnimation> ||
        std::is_same_v<T, HandbremseMode> ||
        std::is_same_v<T, BobbyQuickActions> ||
        std::is_same_v<T, CloudMode>
        , tl::expected<void, std::string>>::type
set_config(ConfigWrapper<T> &config, std::string_view newValue)
{
    if (auto parsed = cpputils::fromString<std::underlying_type_t<T>>(newValue))
        return configs.write_config(config, T(*parsed));
    else
        return tl::make_unexpected(fmt::format("could not parse {}", newValue));
}

void send_config(uint32_t skipCount)
{
    doc.clear();
    doc["type"] = "config";

    if (!cloudClient.is_connected())
        return;

    bool stop{false};

    configs.callForEveryConfig([&](auto &config) {
        if (skipCount > 0)
        {
            --skipCount;
            return;
        }

        if (stop)
            return;

        const std::string_view nvsName{config.nvsName()};
        toArduinoJson(nvsName, config.value(), doc);
        if (doc.overflowed())
        {
            // send data, clear doc and try again
            std::string body;
            doc.remove(nvsName);
            serializeJson(doc, body);
            ESP_LOGI(TAG, "body_size: %d, heap free: %d, stack free: %d", body.size(), esp_get_free_heap_size(), uxTaskGetStackHighWaterMark(nullptr));
            const auto timeout = std::chrono::ceil<espcpputils::ticks>(espchrono::milliseconds32{configs.cloudSettings.cloudTransmitTimeout.value()}).count();
            const auto result_size = cloudClient.send_text(body, timeout);
            if (result_size != body.size())
            {
                ESP_LOGE(TAG, "send_text failed: %d", result_size);
            }
            doc["type"] = "config";
            stop = true;
        }
    });
}

void send_single_config(const std::string &nvsName)
{
    if (!cloudClient.is_connected())
        return;
    doc.clear();
    doc["type"] = "singleConfig";
    bool success{false};
    configs.callForEveryConfig([&](auto &config) {
        if (config.nvsName() == nvsName)
        {
            toArduinoJson(nvsName, config.value(), doc);
            success = true;
        }
    });
    std::string body;
    if (!success)
        doc["error"] = "Config not found";
    serializeJson(doc, body);
    doc.clear();
    const auto timeout = std::chrono::ceil<espcpputils::ticks>(
            espchrono::milliseconds32{configs.cloudSettings.cloudTransmitTimeout.value()}).count();
    cloudClient.send_text(body, timeout);
}

void cloudHeartbeat()
{
    if (!cloudClient.is_connected())
        return;
    const auto timeout = std::chrono::ceil<espcpputils::ticks>(
            espchrono::milliseconds32{configs.cloudSettings.cloudTransmitTimeout.value()}).count();
    cloudClient.send_text(R"({"type":"heartbeat"})", timeout);
}
} // namespace

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

    if (!lastHeartbeat || now - *lastHeartbeat >= 1500ms)
    {
        cloudHeartbeat();
        lastHeartbeat = now;
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

    if (configs.cloudSettings.cloudMode.value() == CloudMode::STATISTICS || configs.cloudSettings.cloudMode.value() == CloudMode::STATISTICS_AND_REMOTE_DISPLAY)
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

        if (!hasAnnouncedItself && configs.cloudSettings.cloudEnabled.value())
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
    else if (cloudClient && !configs.cloudSettings.cloudEnabled.value())
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
    if (configs.cloudSettings.cloudEnabled.value() &&
        !configs.cloudUrl.value().empty() && configs.cloudSettings.cloudMode.value() != CloudMode::INACTIVE)
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

        auto timeout = std::chrono::ceil<espcpputils::ticks>(espchrono::milliseconds32{configs.cloudSettings.cloudTransmitTimeout.value()}).count();
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
    else if (cloudClient && !configs.cloudSettings.cloudEnabled.value())
    {
        destroyCloud();
    }
}

void cloudEventHandler(void *event_handler_arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
    CPP_UNUSED(event_handler_arg);

    const esp_websocket_event_data_t *data = reinterpret_cast<const esp_websocket_event_data_t *>(event_data);

    switch (esp_websocket_event_id_t(event_id))
    {
    case WEBSOCKET_EVENT_CONNECTED:
        ESP_LOGI(TAG, "WEBSOCKET_EVENT_CONNECTED");
        hasAnnouncedItself = false;
        break;
    case WEBSOCKET_EVENT_DISCONNECTED:
        ESP_LOGI(TAG, "WEBSOCKET_EVENT_DISCONNECTED");
        break;
    case WEBSOCKET_EVENT_DATA:
    {
        if (data->op_code != 1) // text
            return;

        doc.clear();

        ESP_LOGI(TAG, "Received: %.*s", data->data_len, data->data_ptr);

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
            doc.clear();
            ESP_LOGI(TAG, "popup: %s, id: %s", text.c_str(), id.c_str());
            BobbyErrorHandler{}.errorOccured(std::move(text));

            if (id.empty())
                return;

            auto timeout = std::chrono::ceil<espcpputils::ticks>(espchrono::milliseconds32{configs.cloudSettings.cloudTransmitTimeout.value()}).count();
            const auto message = fmt::format(R"({{"type":"response","id":"{}"}})", id);
            ESP_LOGI(TAG, "sending response: %s", message.c_str());
            cloudClient.send_text(message, timeout);
            return;
        }
        else if (type == "getConfig")
        {
            JsonVariant _id = doc["id"];
            if (_id.isNull())
            {
                ESP_LOGE(TAG, "getConfig: no id");
                return;
            }
            const auto id = _id.as<uint32_t>();
            doc.clear();
            send_config(id);
            return;
        }
        else if (type == "getSingleConfig")
        {
            JsonVariant nvskey = doc["nvskey"];
            if (nvskey.isNull())
            {
                ESP_LOGE(TAG, "getSingleConfig: nvskey is null");
                return;
            }
            std::string name = nvskey.as<std::string>();
            doc.clear();
            send_single_config(name);
            return;
        }
        else if (type == "setConfig")
        {
            std::string name = doc["nvskey"];
            std::string value = doc["value"];
            doc.clear();
            bool success{false};
            configs.callForEveryConfig([&](auto &config){
                const std::string_view nvsName{config.nvsName()};

                if (nvsName == name)
                {
                    if (const auto result = set_config(config, value); !result)
                    {
                        ESP_LOGE(TAG, "set_config() failed with %s", result.error().c_str());
                        return;
                    }
                    success = true;
                }
            });
            if (!success)
            {
                ESP_LOGE(TAG, "set_config() failed with %s", "unknown config");
                return;
            }
            else
            {
                send_single_config(name);
            }
            return;
        }
        break;
    }
    case WEBSOCKET_EVENT_ERROR:
        ESP_LOGE(TAG, "%s event_id=%s %.*s", event_base, "WEBSOCKET_EVENT_ERROR", data->data_len, data->data_ptr);
        break;
    default:
        ESP_LOGI(TAG, "%s unknown event_id %i", event_base, event_id);
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
        .uri = configs.cloudUrl.value().c_str()
    };

    cloudClient = espcpputils::websocket_client{&config};

    cloudClient.register_events(WEBSOCKET_EVENT_CONNECTED, [](void* event_handler_arg, esp_event_base_t event_base, int32_t event_id, void* event_data) {
        hasAnnouncedItself = false;
    }, nullptr);

    if (const auto result = cloudClient.register_events(WEBSOCKET_EVENT_ANY, &cloudEventHandler, nullptr); result != ESP_OK)
    {
        ESP_LOGE(TAG, "register_events() failed with %s", esp_err_to_name(result));
        return;
    }

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
