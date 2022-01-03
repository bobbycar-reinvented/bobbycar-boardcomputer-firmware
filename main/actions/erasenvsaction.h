#pragma once

// esp-idf includes
#include <esp_log.h>

// local includes
#include "actioninterface.h"
#include "globals.h"
#include "presets.h"

using namespace espgui;

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

        profileSettings = presets::defaultProfileSettings;

        if (profile)
        {
            if (!settingsPersister.openProfile(*profile))
            {
                ESP_LOGE("BOBBY", "openProfile(%hhu) failed", *profile);
                //return;
            }
        }

        if (!settingsPersister.load(profileSettings))
        {
            ESP_LOGE("BOBBY", "load() for settings failed");
            //return;
        }
    }
};
}
