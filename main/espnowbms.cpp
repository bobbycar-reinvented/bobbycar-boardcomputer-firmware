#include "espnowbms.h"
#ifdef FEATURE_ESPNOW_BMS

// esp-idf includes
#include <esp_log.h>

// 3rd party libraries
#include <ArduinoJson.h>

constexpr const char * const TAG = "espnowbms";

namespace bobby::espnowbms {
AntBmsData ant_bms_data;

void init()
{

}

void update()
{

}

void commandReceived(const std::string& command)
{
    ESP_LOGD(TAG, "command received: %s", command.c_str());

    StaticJsonDocument<512> doc;

    DeserializationError error = deserializeJson(doc, command);

    if (error)
    {
        ESP_LOGE(TAG, "deserializeJson() failed: %s", error.c_str());
        return;
    }

    ant_bms_data.parseDoc(doc);

    ESP_LOGD(TAG, "parsed data: %.2fV, %.2fA, %.2fW", ant_bms_data.total_voltage, ant_bms_data.current, ant_bms_data.power);
}
} // namespace bobby::espnowbms
#endif // FEATURE_ESPNOW_BMS
