#pragma once

// local includes
#include "menudisplay.h"
#include "utils.h"
#include "actions/switchscreenaction.h"
#include "icons/back.h"
#include "texts.h"

// forward declares
namespace {
class GenericWifiSettingsMenu;
class StationWifiSettingsMenu;
class AccessPointWifiSettingsMenu;
class SettingsMenu;
} // namespace

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
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,                    SwitchScreenAction<SettingsMenu>, StaticMenuItemIcon<&icons::back>>>();
    }
};
} // namespace
