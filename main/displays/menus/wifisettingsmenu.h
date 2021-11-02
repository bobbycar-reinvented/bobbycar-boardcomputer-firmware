#pragma once

// local includes
#include "menudisplay.h"
#include "utils.h"
#include "actions/switchscreenaction.h"
#include "icons/back.h"
#include "texts.h"

using namespace espgui;

namespace {
class WifiSettingsMenu;

class WifiSettingsMenu :
    public MenuDisplay,
    public StaticText<TEXT_WIFISETTINGS>,
    public BackActionInterface<SwitchScreenAction<SettingsMenu>>
{
public:
    WifiSettingsMenu()
    {
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_GENERICWIFISETTINGS>,     SwitchScreenAction<GenericWifiSettingsMenu>>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_STATIONWIFISETTINGS>,     SwitchScreenAction<StationWifiSettingsMenu>>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ACCESSPOINTWIFISETTINGS>, SwitchScreenAction<AccessPointWifiSettingsMenu>>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,                    SwitchScreenAction<SettingsMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
    }
};
} // namespace
