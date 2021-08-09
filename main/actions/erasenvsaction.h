#pragma once

// esp-idf includes
#include <esp_log.h>

// local includes
#include "actioninterface.h"
#include "globals.h"
#include "presets.h"

namespace {
class EraseNvsAction : public virtual ActionInterface
{
public:
    void triggered() override
    {
        const auto profile = settingsPersister.currentlyOpenProfileIndex();

        if (!settingsPersister.erase())
        {
            ESP_LOGE("BOBBY", "erase() failed");
            //return;
        }

        settings = presets::defaultSettings;

        if (!settingsPersister.openCommon())
        {
            ESP_LOGE("BOBBY", "openCommon() failed");
            //return;
        }

        if (profile)
        {
            if (!settingsPersister.openProfile(*profile))
            {
                ESP_LOGE("BOBBY", "openProfile(%hhu) failed", *profile);
                //return;
            }
        }

        if (!settingsPersister.load(settings))
        {
            ESP_LOGE("BOBBY", "load() failed");
            //return;
        }
    }
};
}
