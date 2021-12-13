constexpr const char * const TAG = "BOBBY_ESP_NOW";
#ifdef FEATURE_ESPNOW
#include "espnowfunctions.h"

#include <string>
#include <espnowwrapper.h>
#include <esp_log.h>

#include "globals.h"

namespace espnow {

std::deque<esp_now_message_t> message_queue{};

void onReceive(const uint8_t *mac_addr, const uint8_t *data, int data_len)
{
    ESP_LOGI(TAG, "Received data");
    const std::string data_str(data, data+data_len);

    size_t sep_pos = data_str.find(":");
    if (std::string::npos != sep_pos)
    {
        std::string msg_type = data_str.substr(0, sep_pos);
        std::string msg = data_str.substr(sep_pos+1, data_str.length()-3); // - 3 may needs to be converted to sep_pos+1
        ESP_LOGI(TAG, "Type: %s - Message: %s", msg_type.c_str(), msg.c_str());

        const esp_now_message_t message{
            .content = msg,
            .type = msg_type
        };
        message_queue.push_back(message);
    }
    else
    {
        ESP_LOGW(TAG, "Invalid message: Could not find ':'");
    }
}

void initESPNow()
{
    ESP_LOGI(TAG, "Initializing esp-now...");

    if (!settings.wifiSettings.wifiApEnabled && !settings.wifiSettings.wifiStaEnabled)
    {
        ESP_LOGW(TAG, "cannot execute esp_now_init(): tcp stack is down.");
        return;
    }

    if (const auto error = esp_now_init(); error != ESP_OK)
    {
        ESP_LOGE(TAG, "esp_now_init() failed with %s", esp_err_to_name(error));
        return;
    }

    if (const auto error = esp_now_register_recv_cb(onReceive); error != ESP_OK)
    {
        ESP_LOGE(TAG, "esp_now_register_recv_cb() failed with %s", esp_err_to_name(error));
        return;
    }
}

void handle()
{
    if(message_queue.size())
    {
        for (const esp_now_message_t &msg : message_queue)
        {
            ESP_LOGW(TAG, "queue has processed message of type '%s' with content '%s'", msg.type.c_str(), msg.content.c_str());
            message_queue.pop_front();

            if (msg.type == "T")
            {
                // convert msg.content into uint64_t
                // onRecvTs(converted);
            }
        }
        for (const esp_now_message_t &msg : message_queue)
        {
            ESP_LOGI(TAG, "%s", msg.content.c_str());
        }
    }
}

void onRecvTs(uint64_t millis)
{

}

} // namespace espnow
#endif
