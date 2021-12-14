constexpr const char * const TAG = "BOBBY_ESP_NOW";
#ifdef FEATURE_ESPNOW
#include "espnowfunctions.h"

#include <string>

#include <espchrono.h>
#include <esp_log.h>
#include <numberparsing.h>

#include "globals.h"
#include "utils.h"
#include "time_bobbycar.h"

namespace espnow {

uint16_t lastYear; // Used for esp-now timesync

std::deque<esp_now_message_t> message_queue{};
std::list<esp_now_peer_info_t> peers{};
uint8_t initialized{0};

bool receiveTimeStamp{true};
bool receiveTsFromOtherBobbycars{true};

void onReceive(const uint8_t *mac_addr, const uint8_t *data, int data_len)
{
    ESP_LOGD(TAG, "Received data");
    const std::string data_str(data, data+data_len);

    size_t sep_pos = data_str.find(":");
    if (std::string::npos != sep_pos)
    {
        std::string msg_type = data_str.substr(0, sep_pos);
        std::string msg = data_str.substr(sep_pos+1, data_str.length()-3); // - 3 may needs to be converted to sep_pos+1
        ESP_LOGD(TAG, "Type: %s - Message: %s", msg_type.c_str(), msg.c_str());

        const esp_now_message_t message{
            .content = msg,
            .type = msg_type
        };
        message_queue.push_back(message);
    }
    else
    {
        ESP_LOGW(TAG, "Invalid message: Could not find ':' (%s)", data_str.c_str());
    }
}

void initESPNow()
{
    ESP_LOGI(TAG, "Initializing esp-now...");

    if (initialized < 1)
    {
        if (!settings.wifiSettings.wifiApEnabled && !settings.wifiSettings.wifiStaEnabled)
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
/*
        if (settings.wifiSettings.wifiApEnabled)
            peer.ifidx = WIFI_IF_AP;
        else if (settings.wifiSettings.wifiStaEnabled)*/
            peer.ifidx = WIFI_IF_STA;

        if (const auto error = esp_now_add_peer(&peers.back()); error != ESP_OK)
        {
            ESP_LOGE(TAG, "esp_now_add_peer() failed with %s", esp_err_to_name(error));
            return;
        }
        else
            initialized = 4;
    }

    initialized = 255;
}

void handle()
{
    if (initialized < 255 && (settings.wifiSettings.wifiApEnabled || settings.wifiSettings.wifiStaEnabled))
    {
        initESPNow();
        return;
    }

    if(message_queue.size())
    {
        for (const esp_now_message_t &msg : message_queue)
        {
            ESP_LOGD(TAG, "queue has processed message of type '%s' with content '%s'", msg.type.c_str(), msg.content.c_str());
            message_queue.pop_front();

            if (msg.type == "T")
            {
                if (!receiveTimeStamp || !settings.espnow.syncTime)
                    return;

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
                if (!receiveTsFromOtherBobbycars || !settings.espnow.syncTimeWithOthers)
                    return;

                if (const auto result = cpputils::fromString<uint64_t>(msg.content); result)
                {
                    onRecvTs(*result, true);
                }
                else
                {
                    ESP_LOGW(TAG, "could not parse number: %.*s", result.error().size(), result.error().data());
                }
            }
            else
            {
                ESP_LOGI(TAG, "Unkown Type: %s - Message: %s", msg.type.c_str(), msg.content.c_str());
            }
        }
    }
}

void onRecvTs(uint64_t millis, bool isFromBobbycar)
{
    const auto milliseconds = std::chrono::milliseconds(millis);
    const auto timepoint = espchrono::utc_clock::time_point(milliseconds);
    ESP_LOGW(TAG, "setting current time to %s", espchrono::toString(timepoint.time_since_epoch()).c_str());
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

esp_err_t send_espnow_message(std::string message)
{
    if (initialized < 255)
        return ESP_ERR_ESPNOW_NOT_INIT;

    if (!settings.wifiSettings.wifiApEnabled && !settings.wifiSettings.wifiStaEnabled)
    {
        return ESP_ERR_ESPNOW_IF;
    }

    if (peers.size() < 1)
    {
        return ESP_FAIL;
    }

    for (const auto &peer : peers)
    {
        if(const auto error = esp_now_send(peer.peer_addr, (const uint8_t*)message.data(), message.size()); error != ESP_OK)
        {
            return error;
        }
        else
            ESP_LOGI(TAG, "Successfully executed esp_now_send()");
    }
    return ESP_OK;
}

} // namespace espnow
#endif
