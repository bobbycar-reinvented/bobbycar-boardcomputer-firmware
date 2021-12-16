constexpr const char * const TAG = "BOBBY_ESP_NOW";
#ifdef FEATURE_ESPNOW
#include "espnowfunctions.h"

#include <string>
#include <espnowwrapper.h>
#include <esp_log.h>

namespace espnow {

void onReceive(const uint8_t *mac_addr, const uint8_t *data, int data_len)
{
    const std::string data_str(data, data+data_len);

    size_t sep_pos = data_str.find(":");
    if (std::string::npos != sep_pos)
    {
        std::string msg_type = data_str.substr(0, sep_pos);
        std::string msg = data_str.substr(sep_pos, data_str.length()-1);
        ESP_LOGI(TAG, "Type: %s - Message: %s", msg_type.c_str(), msg.c_str());
    }
    else
    {
        ESP_LOGW(TAG, "Invalid message: Could not find ':'");
    }
}

void initESPNow()
{
    ESP_LOGI(TAG, "Initializing esp now...");
    ESPNow.reg_recv_cb(onReceive);
    ESPNow.init();
}

void onRecvTs(uint64_t millis)
{

}

} // namespace espnow
#endif
