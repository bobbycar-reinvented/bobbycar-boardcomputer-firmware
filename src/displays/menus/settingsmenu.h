#pragma once

// Arduino includes
#include <HardwareSerial.h>

// local includes
#include "menudisplay.h"
#include "containermenudefinition.h"
#include "utils.h"
#include "actions/toggleboolaction.h"
#include "actions/switchscreenaction.h"
#include "checkboxicon.h"
#include "icons/wifi.h"
#ifdef FEATURE_BLUETOOTH
#include "icons/bluetooth.h"
#endif
#include "icons/hardware.h"
#include "icons/buzzer.h"
#include "icons/info.h"
#include "icons/back.h"
#include "texts.h"
#include "globals.h"
#include "settingsaccessors.h"

// forward declares
namespace {
class LimitsSettingsMenu;
class WifiSettingsMenu;
class BluetoothSettingsMenu;
class ModesSettingsMenu;
class ControllerHardwareSettingsMenu;
class BoardcomputerHardwareSettingsMenu;
class BuzzerMenu;
class AboutMenu;
class MainMenu;
}

namespace {
struct FrontLedAccessor : public RefAccessor<bool> { bool &getRef() const override { return controllers.front.command.led; } };
struct BackLedAccessor : public RefAccessor<bool> { bool &getRef() const override { return controllers.back.command.led; } };

class SettingsMenu :
    public MenuDisplay,
    public StaticText<TEXT_SETTINGS>,
    public BackActionInterface<SwitchScreenAction<MainMenu>>,
    public ContainerMenuDefinition
{
public:
    SettingsMenu()
    {
        constructItem<makeComponent<MenuItem, StaticText<TEXT_LIMITSSETTINGS>,                SwitchScreenAction<LimitsSettingsMenu>>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_WIFISETTINGS>,                  SwitchScreenAction<WifiSettingsMenu>, StaticMenuItemIcon<&icons::wifi>>>();
#ifdef FEATURE_BLUETOOTH
        constructItem<makeComponent<MenuItem, StaticText<TEXT_BLUETOOTHSETTINGS>,             SwitchScreenAction<BluetoothSettingsMenu>, StaticMenuItemIcon<&icons::bluetooth>>>();
#endif
        constructItem<makeComponent<MenuItem, StaticText<TEXT_MODESSETTINGS>,                 SwitchScreenAction<ModesSettingsMenu>>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_CONTROLLERHARDWARESETTINGS>,    SwitchScreenAction<ControllerHardwareSettingsMenu>, StaticMenuItemIcon<&icons::hardware>>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_BOARDCOMPUTERHARDWARESETTINGS>, SwitchScreenAction<BoardcomputerHardwareSettingsMenu>, StaticMenuItemIcon<&icons::hardware>>>();
#if defined(FEATURE_BLUETOOTH) && defined(FEATURE_BMS)
        constructItem<makeComponent<MenuItem, StaticText<TEXT_AUTOCONNECTBMS>,                ToggleBoolAction, CheckboxIcon, AutoConnectBmsAccessor>>();
#endif
        constructItem<makeComponent<MenuItem, StaticText<TEXT_BUZZER>,                        SwitchScreenAction<BuzzerMenu>, StaticMenuItemIcon<&icons::buzzer>>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_FRONTLED>,                      ToggleBoolAction, CheckboxIcon, FrontLedAccessor>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_BACKLED>,                       ToggleBoolAction, CheckboxIcon, BackLedAccessor>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_ABOUT>,                         SwitchScreenAction<AboutMenu>, StaticMenuItemIcon<&icons::info>>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,                          SwitchScreenAction<MainMenu>, StaticMenuItemIcon<&icons::back>>>();
    }
};
} // namespace
