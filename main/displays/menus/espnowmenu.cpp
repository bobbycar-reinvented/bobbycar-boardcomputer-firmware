#include "espnowmenu.h"

#ifdef FEATURE_ESPNOW
#include "actions/dummyaction.h"
#include "actions/switchscreenaction.h"
#include "actions/toggleboolaction.h"
#include "checkboxicon.h"
#include "icons/back.h"
#include "icons/time.h"
#include "settingsmenu.h"

using namespace espgui;

namespace espnowmenu {
} // namespace

EspNowMenu::EspNowMenu() {
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ESPNOW_SENDTSMSG>, espnowmenu::SendBobbycarTimesyncMessageAction, StaticMenuItemIcon<&bobbyicons::time>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ESPNOW_RECEIVETS>, ToggleBoolAction, CheckboxIcon, espnowmenu::ReceiveTimeStampAccessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ESPNOW_RECEIVETSFROMBOBBY>, ToggleBoolAction, CheckboxIcon, espnowmenu::ReceiveTsFromOtherBobbycarsAccessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>, SwitchScreenAction<SettingsMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
}

void EspNowMenu::back()
{
    switchScreen<SettingsMenu>();
}
#endif
