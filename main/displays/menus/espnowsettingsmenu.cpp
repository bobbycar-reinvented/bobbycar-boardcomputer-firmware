#include "espnowsettingsmenu.h"

#ifdef FEATURE_ESPNOW
#include "accessors/settingsaccessors.h"
#include "actions/dummyaction.h"
#include "actions/switchscreenaction.h"
#include "actions/toggleboolaction.h"
#include "checkboxicon.h"
#include "icons/back.h"
#include "icons/time.h"
#include "espnowmenu.h"

using namespace espgui;

namespace espnowsettingsmenu {
} // namespace

EspNowSettingsMenu::EspNowSettingsMenu() {
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ESPNOW_SYNCTIME>, ToggleBoolAction, CheckboxIcon, ESPNowSyncTimeEnabledAccessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ESPNOW_SYNCWITHOTHERS>, ToggleBoolAction, CheckboxIcon, ESPNowSyncTimeWithOthersEnabledAccessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ESPNOW_SYNCBLINK>, ToggleBoolAction, CheckboxIcon, ESPNowSyncBlinkEnabledAccessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>, SwitchScreenAction<EspNowMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
}

void EspNowSettingsMenu::back()
{
    switchScreen<EspNowMenu>();
}
#endif
