#pragma once

// esp-idf includes
#include <esp_log.h>

// local includes
#include "actioninterface.h"
#include "wifi_bobbycar.h"

using namespace espgui;

namespace {
class WifiScanAction : public virtual ActionInterface
{
public:
    void triggered() override
    {
        if (const auto result = wifi_scan(); result != ESP_OK)
        {
            ESP_LOGE("BOBBY", "wifi_scan() failed with %s", esp_err_to_name(result));
            return;
        }
    }
};
}
