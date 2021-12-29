#include "espnowmenu.h"

#ifdef FEATURE_ESPNOW
// 3rdparty lib includes
#include "actions/dummyaction.h"
#include "actions/switchscreenaction.h"
#include "icons/back.h"

// local includes
#include "icons/settings.h"
#include "icons/time.h"
#include "displays/menus/espnowsettingsmenu.h"
#include "displays/menus/settingsmenu.h"
#include "bobbycheckbox.h"

using namespace espgui;

namespace espnowmenu {
} // namespace

EspNowMenu::EspNowMenu() {
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ESPNOW_SENDTSMSG>, espnowmenu::SendBobbycarTimesyncMessageAction, StaticMenuItemIcon<&bobbyicons::time>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ESPNOW_RECEIVETS>, BobbyCheckbox, espnowmenu::ReceiveTimeStampAccessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ESPNOW_RECEIVETSFROMBOBBY>, BobbyCheckbox, espnowmenu::ReceiveTsFromOtherBobbycarsAccessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ESPNOW_SETTINGS>, SwitchScreenAction<EspNowSettingsMenu>, StaticMenuItemIcon<&bobbyicons::settings>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>, SwitchScreenAction<SettingsMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
}

void EspNowMenu::back()
{
    switchScreen<SettingsMenu>();
}
#endif
