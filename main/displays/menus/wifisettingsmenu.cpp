#include "wifisettingsmenu.h"

// 3rdparty lib includes
#include "actions/switchscreenaction.h"
#include "icons/back.h"

// local includes
#include "utils.h"
#include "displays/menus/genericwifisettingsmenu.h"
#include "displays/menus/stationwifisettingsmenu.h"
#include "displays/menus/accesspointwifisettingsmenu.h"
#include "displays/menus/settingsmenu.h"

using namespace espgui;

WifiSettingsMenu::WifiSettingsMenu()
{
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_GENERICWIFISETTINGS>,     SwitchScreenAction<GenericWifiSettingsMenu>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_STATIONWIFISETTINGS>,     SwitchScreenAction<StationWifiSettingsMenu>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ACCESSPOINTWIFISETTINGS>, SwitchScreenAction<AccessPointWifiSettingsMenu>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,                    SwitchScreenAction<SettingsMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
}

void WifiSettingsMenu::back()
{
    switchScreen<SettingsMenu>();
}
