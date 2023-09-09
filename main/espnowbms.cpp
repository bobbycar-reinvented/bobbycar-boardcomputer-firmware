#include "espnowbms.h"
#ifdef FEATURE_ESPNOW_BMS

// esp-idf includes
#include <esp_log.h>

// 3rd party libraries
#include <ArduinoJson.h>

constexpr const char * const TAG = "espnowbms";

namespace bobby::espnowbms {
cpputils::DelayedConstruction<AntBmsData> ant_bms_data;

void init() {}

void update()
{
    using namespace std::chrono_literals;

    if (!ant_bms_data.constructed())
        return;

    if (ant_bms_data->last_update.has_value() && espchrono::ago(*ant_bms_data->last_update) > 10s)
        ant_bms_data.destruct();
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

    if (!ant_bms_data.constructed())
    {
        ant_bms_data.construct();
    }

    if (!ant_bms_data.constructed())
        return;

    ant_bms_data->parseDoc(doc);
}
} // namespace bobby::espnowbms
#endif // FEATURE_ESPNOW_BMS
