#pragma once

#include <HardwareSerial.h>

#include "menudisplay.h"
#include "staticmenudefinition.h"
#include "changevaluedisplay.h"
#include "menuitem.h"
#include "actions/dummyaction.h"
#include "actions/toggleboolaction.h"
#include "actions/switchscreenaction.h"
#include "checkboxicon.h"
#include "icons/back.h"
#include "wifitexthelpers.h"
#include "wifiaccessors.h"
#include "texts.h"

namespace {
class GenericWifiSettingsMenu;
class WifiSettingsMenu;
}

namespace {
using WifiModeChangeScreen = makeComponent<
    ChangeValueDisplay<wifi_mode_t>,
    StaticText<TEXT_WIFICHANGEMODE>,
    WifiModeAccessor,
    BackActionInterface<SwitchScreenAction<GenericWifiSettingsMenu>>,
    SwitchScreenAction<GenericWifiSettingsMenu>
>;

using WifiTxPowerChangeScreen = makeComponent<
    ChangeValueDisplay<wifi_power_t>,
    StaticText<TEXT_WIFICHANGETXPOWER>,
    WifiTxPowerAccessor,
    BackActionInterface<SwitchScreenAction<GenericWifiSettingsMenu>>,
    SwitchScreenAction<GenericWifiSettingsMenu>
>;

class GenericWifiSettingsMenu :
    public MenuDisplay,
    public StaticText<TEXT_GENERICWIFISETTINGS>,
    public BackActionInterface<SwitchScreenAction<WifiSettingsMenu>>,
    public StaticMenuDefinition<
        makeComponent<MenuItem, WifiStatusBitsText,                 DisabledColor, DummyAction>,
        makeComponent<MenuItem, WifiChannelText,                    DisabledColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_WIFICHANGEMODE>,    SwitchScreenAction<WifiModeChangeScreen>>,
        makeComponent<MenuItem, StaticText<TEXT_WIFICHANGESLEEP>,   ToggleBoolAction, CheckboxIcon, WifiSleepAccessor>,
        makeComponent<MenuItem, StaticText<TEXT_WIFICHANGETXPOWER>, SwitchScreenAction<WifiTxPowerChangeScreen>>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,              SwitchScreenAction<WifiSettingsMenu>, StaticMenuItemIcon<&icons::back>>
    >
{};
}
