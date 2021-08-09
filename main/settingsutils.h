#pragma once

// esp-idf includes
#include <esp_log.h>

// local includes
#include "globals.h"
#include "presets.h"

namespace {
void switchProfile(uint8_t index)
{
    settings = presets::defaultSettings;

    if (!settingsPersister.openProfile(index))
    {
        ESP_LOGE("BOBBY", "openProfile() failed");
        return;
    }

    if (!settingsPersister.load(settings))
    {
        ESP_LOGE("BOBBY", "load() failed");
        return;
    }
}
}
