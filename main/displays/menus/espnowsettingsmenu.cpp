#include "espnowsettingsmenu.h"

#ifdef FEATURE_ESPNOW
// 3rdparty lib includes
#include "actions/dummyaction.h"
#include "actions/switchscreenaction.h"
#include "icons/back.h"

// local includes
#include "accessors/settingsaccessors.h"
#include "icons/time.h"
#include "espnowmenu.h"
#include "bobbycheckbox.h"

using namespace espgui;

namespace espnowsettingsmenu {
} // namespace

EspNowSettingsMenu::EspNowSettingsMenu() {
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ESPNOW_SYNCTIME>, BobbyCheckbox, ESPNowSyncTimeEnabledAccessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ESPNOW_SYNCWITHOTHERS>, BobbyCheckbox, ESPNowSyncTimeWithOthersEnabledAccessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ESPNOW_SYNCBLINK>, BobbyCheckbox, ESPNowSyncBlinkEnabledAccessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>, SwitchScreenAction<EspNowMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
}

void EspNowSettingsMenu::back()
{
    switchScreen<EspNowMenu>();
}
#endif
