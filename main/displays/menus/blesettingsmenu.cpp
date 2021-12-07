#include "blesettingsmenu.h"

// local includes
#include "accessors/settingsaccessors.h"
#include "actions/dummyaction.h"
#include "actions/switchscreenaction.h"
#include "actions/toggleboolaction.h"
#include "bletexthelpers.h"
#include "checkboxicon.h"
#include "displays/menus/settingsmenu.h"
#include "icons/back.h"
#include "texts.h"

#ifdef FEATURE_BLE

using namespace espgui;

BleSettingsMenu::BleSettingsMenu()
{
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BLEENABLED>, ToggleBoolAction, CheckboxIcon, BleEnabledAccessor>>();
    constructMenuItem<makeComponent<MenuItem, BleServerPeerDevicesText,    DisabledColor, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, BleCharacSubscribedText,     DisabledColor, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,       SwitchScreenAction<SettingsMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
}

void BleSettingsMenu::back()
{
    switchScreen<SettingsMenu>();
}
#endif
