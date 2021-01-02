#pragma once

// local includes
#include "changevaluedisplay.h"
#include "menudisplay.h"
#include "containermenudefinition.h"
#include "utils.h"
#include "actions/switchscreenaction.h"
#include "actions/toggleboolaction.h"
#include "checkboxicon.h"
#include "icons/scan.h"
#include "icons/back.h"
#include "texts.h"
#include "settingsaccessors.h"

// forward declares
namespace {
class GenericWifiSettingsMenu;
class StationWifiSettingsMenu;
class WifiScanMenu;
class AccessPointWifiSettingsMenu;
class SettingsMenu;
} // namespace

namespace {
class WifiSettingsMenu;

using AutoWifiModeChangeDisplay = makeComponent<
    ChangeValueDisplay<wifi_mode_t>,
    StaticText<TEXT_AUTOWIFIMODE>,
    AutoWifiModeAccessor,
    BackActionInterface<SwitchScreenAction<WifiSettingsMenu>>,
    SwitchScreenAction<WifiSettingsMenu>
>;

class WifiSettingsMenu :
    public MenuDisplay,
    public StaticText<TEXT_WIFISETTINGS>,
    public BackActionInterface<SwitchScreenAction<SettingsMenu>>,
    public ContainerMenuDefinition
{
public:
    WifiSettingsMenu()
    {
        constructItem<makeComponent<MenuItem, StaticText<TEXT_AUTOWIFIMODE>,            SwitchScreenAction<AutoWifiModeChangeDisplay>>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_AUTOENABLEAP>,            ToggleBoolAction, CheckboxIcon, AutoEnableApAccessor>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_GENERICWIFISETTINGS>,     SwitchScreenAction<GenericWifiSettingsMenu>>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_STATIONWIFISETTINGS>,     SwitchScreenAction<StationWifiSettingsMenu>>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_WIFISCAN>,                SwitchScreenAction<WifiScanMenu>, StaticMenuItemIcon<&icons::scan>>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_ACCESSPOINTWIFISETTINGS>, SwitchScreenAction<AccessPointWifiSettingsMenu>>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,                    SwitchScreenAction<SettingsMenu>, StaticMenuItemIcon<&icons::back>>>();
    }
};
} // namespace
