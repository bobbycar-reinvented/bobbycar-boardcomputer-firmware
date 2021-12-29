#include "blesettingsmenu.h"

// 3rdparty lib includes
#include "actions/dummyaction.h"
#include "actions/switchscreenaction.h"
#include "icons/back.h"

// local includes
#include "accessors/settingsaccessors.h"
#include "bletexthelpers.h"
#include "displays/menus/settingsmenu.h"
#include "bobbycheckbox.h"
#include "texts.h"

#ifdef FEATURE_BLE

using namespace espgui;

BleSettingsMenu::BleSettingsMenu()
{
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BLEENABLED>, BobbyCheckbox, BleEnabledAccessor>>();
    constructMenuItem<makeComponent<MenuItem, BleServerPeerDevicesText,    DisabledColor, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, BleCharacSubscribedText,     DisabledColor, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,       SwitchScreenAction<SettingsMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
}

void BleSettingsMenu::back()
{
    switchScreen<SettingsMenu>();
}
#endif
