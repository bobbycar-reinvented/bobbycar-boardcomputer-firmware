#include "espnowfunctions.h"

// 3rdparty lib includes
#include <espchrono.h>
#include <esp_log.h>
#include <numberparsing.h>
#include <espwifistack.h>

// local includes
#include "globals.h"
#include "utils.h"
#include "time_bobbycar.h"
#include "newsettings.h"
#include "bobbyhupe.h"
#include "bobbyblinker.h"

namespace espnow {
uint16_t lastYear; // Used for esp-now timesync

std::deque<esp_now_message_t> message_queue{};
std::vector<esp_now_peer_info_t> peers{};
uint8_t initialized{0};

bool receiveTimeStamp{true};
bool receiveTsFromOtherBobbycars{true};

namespace {
constexpr const char * const TAG = "BOBBY_ESP_NOW";
} // namespace

bool espnow_init_allowed()
{
    const auto wifi_mode = wifi_stack::get_wifi_mode();
    return
    (
        (configs.espnow.syncBlink.value || configs.espnow.syncTime.value || configs.espnow.syncTimeWithOthers.value)
        &&
        (
            (configs.wifiApEnabled.value && wifi_stack::get_wifi_mode() == WIFI_MODE_AP)
            ||
            (
                configs.wifiStaEnabled.value
                &&
                wifi_stack::get_sta_status() != wifi_stack::WiFiStaStatus::NO_SHIELD
                &&
                (
                    wifi_mode == WIFI_MODE_STA ||
                    wifi_mode == WIFI_MODE_APSTA
                )
            )
        )
    );
}

namespace {
extern "C" void onReceive(const uint8_t *mac_addr, const uint8_t *data, int data_len)
{
    ESP_LOGD(TAG, "Received data");
    const std::string_view data_str{(const char *)data, size_t(data_len)};

    size_t sep_pos = data_str.find(":");
    if (std::string_view::npos != sep_pos)
    {
        esp_now_message_t msg{
            .content = std::string{data_str.substr(sep_pos+1, data_str.length()-sep_pos-1)},
            .type = std::string{data_str.substr(0, sep_pos)}
        };

        ESP_LOGD(TAG, "Type: %s - Message: %s", msg.type.c_str(), msg.content.c_str());

        message_queue.push_back(msg);
    }
    else
    {
        ESP_LOGW(TAG, "Invalid message: Could not find ':' (%.*s)", data_str.size(), data_str.data());
    }
}
} // namespace

void initESPNow()
{
    ESP_LOGI(TAG, "Initializing esp-now...");

    if (initialized < 1)
    {
        if (!configs.wifiApEnabled.value && (!configs.wifiStaEnabled.value && wifi_stack::get_sta_status() == wifi_stack::WiFiStaStatus::NO_SHIELD) || (wifi_stack::get_wifi_mode() != wifi_mode_t::WIFI_MODE_STA && wifi_stack::get_wifi_mode() != wifi_mode_t::WIFI_MODE_AP && wifi_stack::get_wifi_mode() != wifi_mode_t::WIFI_MODE_APSTA) && (configs.espnow.syncBlink.value || configs.espnow.syncTime.value || configs.espnow.syncTimeWithOthers.value))
        {
            ESP_LOGW(TAG, "cannot execute esp_now_init(): tcp stack is down.");
            return;
        }
        else
            initialized = 1;
    }

    if (initialized < 2)
    {
        if (const auto error = esp_now_init(); error != ESP_OK)
        {
            ESP_LOGE(TAG, "esp_now_init() failed with %s", esp_err_to_name(error));
            return;
        }
        else
            initialized = 2;
    }

    if (initialized < 3)
    {
        if (const auto error = esp_now_register_recv_cb(onReceive); error != ESP_OK)
        {
            ESP_LOGE(TAG, "esp_now_register_recv_cb() failed with %s", esp_err_to_name(error));
            return;
        }
        else
            initialized = 3;
    }

    if (initialized < 4)
    {
        peers.push_back(esp_now_peer_info_t{});
        esp_now_peer_info_t &peer = peers.back();
        std::memcpy(peer.peer_addr, broadcast_address, sizeof(peer.peer_addr));
        peer.channel = 0;

        if (configs.wifiApEnabled.value)
            peer.ifidx = WIFI_IF_AP;
        else if (configs.wifiStaEnabled.value)
            peer.ifidx = WIFI_IF_STA;
        else
        {
            ESP_LOGE(TAG, "Interfaces not ready.");
            return;
        }

        if (const auto error = esp_now_add_peer(&peers.back()); error != ESP_OK)
        {
            ESP_LOGE(TAG, "esp_now_add_peer() failed with %s", esp_err_to_name(error));
            return;
        }
        else
            initialized = 4;
    }

    initialized = 255;
    ESP_LOGI(TAG, "Init done.");
}

void handle()
{
    bobbyhupe::handle_hupe();
    bobbyblinker::handle_blinker();
    if (initialized < 255 && espnow_init_allowed())
    {
        initESPNow();
        return;
    }
    else if (!espnow_init_allowed() && initialized >= 255)
    {
        if (initialized > 0)
        {
            if (initialized >= 4) // peer
            {
                for (const auto &peer : peers)
                {
                    if (const auto error = esp_now_del_peer(peer.peer_addr); error != ESP_OK)
                    {
                        if (error == ESP_ERR_ESPNOW_NOT_FOUND)
                        {
                            initialized = 0;
                            return;
                        }
                        ESP_LOGE(TAG, "esp_now_del_peer() failed with %s", esp_err_to_name(error));
                        return;
                    }
                }
                initialized--;
            }

            if (initialized >= 3) // callback
            {
                if (const auto error = esp_now_unregister_recv_cb(); error != ESP_OK)
                {
                    ESP_LOGE(TAG, "esp_now_unregister_recv_cb() failed with %s", esp_err_to_name(error));
                    return;
                }
                else if (error == ESP_ERR_ESPNOW_NOT_FOUND)
                {
                    initialized = 0;
                }
                else
                    initialized--;
            }

            if (initialized >= 2) // esp deinit
            {
                if (const auto error = esp_now_deinit(); error != ESP_OK)
                {
                    ESP_LOGE(TAG, "esp_now_deinit() failed with %s", esp_err_to_name(error));
                    return;
                }
                else if (error == ESP_ERR_ESPNOW_NOT_FOUND)
                {
                    initialized = 0;
                }
                else
                    initialized--;
            }

            initialized = 0;
            ESP_LOGI(TAG, "Deinit done.");
        }
        return;
    }

    if (message_queue.size())
    {
        for (const esp_now_message_t &msg : message_queue)
        {
            if (msg.type == "T")
            {
                if (!receiveTimeStamp || !configs.espnow.syncTime.value)
                    goto clear;

                if (const auto result = cpputils::fromString<uint64_t>(msg.content); result)
                {
                    onRecvTs(*result);
                }
                else
                {
                    ESP_LOGW(TAG, "could not parse number: %.*s", result.error().size(), result.error().data());
                }
            }
            else if (msg.type == "BOBBYT")
            {
                if (!receiveTsFromOtherBobbycars || !configs.espnow.syncTimeWithOthers.value)
                    goto clear;

                if (const auto result = cpputils::fromString<uint64_t>(msg.content); result)
                {
                    ESP_LOGI(TAG, "setting current time to %" PRIu64, *result);
                    onRecvTs(*result, true);
                }
                else
                {
                    ESP_LOGW(TAG, "could not parse number: %.*s", result.error().size(), result.error().data());
                }
            }
            else
            {
                ESP_LOGI(TAG, "Unknown Type: %s - Message: %s", msg.type.c_str(), msg.content.c_str());
            }
        }
clear:
        message_queue.erase(std::begin(message_queue), std::end(message_queue));
    }
}

void onRecvTs(uint64_t millis, bool isFromBobbycar)
{
    const auto milliseconds = std::chrono::milliseconds(millis);
    const auto timepoint = espchrono::utc_clock::time_point(milliseconds);
    // ESP_LOGW(TAG, "setting current time to %s", espchrono::toString(timepoint.time_since_epoch()).c_str());
    time_set_now(timepoint);

    if (receiveTimeStamp)
    {
        if (const auto thisYear = int(espchrono::toDateTime(espchrono::utc_clock::now()).date.year()); abs(thisYear - espnow::lastYear) > 1)
        {
            espnow::lastYear = thisYear;
            receiveTimeStamp = false;
        }
    }

    receiveTsFromOtherBobbycars = false;
}

esp_err_t send_espnow_message(std::string_view message)
{
    if (initialized < 255)
        return ESP_ERR_ESPNOW_NOT_INIT;

    if (!configs.wifiApEnabled.value && !configs.wifiStaEnabled.value)
    {
        return ESP_ERR_ESPNOW_IF;
    }

    if (peers.size() < 1)
    {
        return ESP_FAIL;
    }

    for (auto &peer : peers)
    {

        if (configs.wifiApEnabled.value)
            peer.ifidx = WIFI_IF_AP;
        else if (configs.wifiStaEnabled.value)
            peer.ifidx = WIFI_IF_STA;
        else
            return ESP_ERR_ESPNOW_IF;

        const auto timeBefore = espchrono::millis_clock::now();

        if(const auto error = esp_now_send(broadcast_address, (const uint8_t*)message.data(), message.size()); error != ESP_OK)
        {
            return error;
        }
        else
        {
            const auto timeAfter = espchrono::millis_clock::now();
            ESP_LOGD(TAG, "Successfully executed esp_now_send(): Took %lldms", std::chrono::floor<std::chrono::milliseconds>(timeAfter-timeBefore).count());
        }
    }
    return ESP_OK;
}

} // namespace espnow
