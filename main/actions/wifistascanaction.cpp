#include "wifistascanaction.h"

// esp-idf includes
#include <esp_log.h>

// local includes
#include "wifi_bobbycar.h"

namespace {
constexpr const char * const TAG = "BOBBY";
} // namespace

void WifiStaScanAction::triggered()
{
    if (const auto result = wifi_scan(); result != ESP_OK)
    {
        ESP_LOGE(TAG, "wifi_scan() failed: %s", esp_err_to_name(result));
        return;
    }
}
