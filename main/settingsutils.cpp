#include "settingsutils.h"

// esp-idf includes
#include <esp_log.h>

// local includes
#include "globals.h"
#include "newsettings.h"
#include "presets.h"

namespace bobby::settingsutils {

void switchProfile(uint8_t index)
{
#ifdef SIMPLIFIED_TRIGGER_TRIGGERONPRESET
    if (index == SIMPLIFIED_TRIGGER_TRIGGERONPRESET)
    {
        simplified = true;
        if (const auto val = configs.lockscreen.rememberMe.value(); val)
            configs.write_config(configs.lockscreen.rememberMe, std::max(1UL, *val - 20*100000));
#ifdef SETTINGSUTILS_PLUGIN
#include SETTINGSUTILS_PLUGIN
#endif
        return;
    }
#endif

    profileSettings = presets::defaultProfileSettings;

    if (!settingsPersister.openProfile(index))
    {
        ESP_LOGE("BOBBY", "openProfile() failed");
        return;
    }

    if (!settingsPersister.load(profileSettings))
    {
        ESP_LOGE("BOBBY", "load() for settings failed");
        return;
    }
}

} // namespace bobby::settingsutils
