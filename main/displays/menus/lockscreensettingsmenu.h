#pragma once

// local includes
#include "menudisplay.h"
#include "menuitem.h"
#include "actions/toggleboolaction.h"
#include "actions/switchscreenaction.h"
#include "texts.h"
#include "icons/back.h"
#include "checkboxicon.h"
#include "globals.h"
#include "accessors/settingsaccessors.h"
#include "changevaluedisplay.h"

using namespace espgui;

namespace {
using LockscreenPinDigit0ChangeScreen = makeComponent<
    ChangeValueDisplay<int8_t>,
    StaticText<TEXT_PINDIGIT0>,
    LockscreenPinDigitAccessor<0>,
    BackActionInterface<SwitchScreenAction<LockscreenSettingsMenu>>,
    SwitchScreenAction<LockscreenSettingsMenu>
>;

using LockscreenPinDigit1ChangeScreen = makeComponent<
    ChangeValueDisplay<int8_t>,
    StaticText<TEXT_PINDIGIT1>,
    LockscreenPinDigitAccessor<1>,
    BackActionInterface<SwitchScreenAction<LockscreenSettingsMenu>>,
    SwitchScreenAction<LockscreenSettingsMenu>
>;

using LockscreenPinDigit2ChangeScreen = makeComponent<
    ChangeValueDisplay<int8_t>,
    StaticText<TEXT_PINDIGIT2>,
    LockscreenPinDigitAccessor<2>,
    BackActionInterface<SwitchScreenAction<LockscreenSettingsMenu>>,
    SwitchScreenAction<LockscreenSettingsMenu>
>;

using LockscreenPinDigit3ChangeScreen = makeComponent<
    ChangeValueDisplay<int8_t>,
    StaticText<TEXT_PINDIGIT3>,
    LockscreenPinDigitAccessor<3>,
    BackActionInterface<SwitchScreenAction<LockscreenSettingsMenu>>,
    SwitchScreenAction<LockscreenSettingsMenu>
>;

class LockscreenSettingsMenu :
    public MenuDisplay,
    public StaticText<TEXT_LOCKSCREENSETTINGS>,
    public BackActionInterface<SwitchScreenAction<BoardcomputerHardwareSettingsMenu>>
{
public:
    LockscreenSettingsMenu()
    {
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ALLOWPRESETSWITCH>, ToggleBoolAction, CheckboxIcon, LockscreenAllowPresetSwitchAccessor>>();
        constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_PINDIGIT0, LockscreenPinDigitAccessor<0>>, SwitchScreenAction<LockscreenPinDigit0ChangeScreen>>>();
        constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_PINDIGIT1, LockscreenPinDigitAccessor<1>>, SwitchScreenAction<LockscreenPinDigit1ChangeScreen>>>();
        constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_PINDIGIT2, LockscreenPinDigitAccessor<2>>, SwitchScreenAction<LockscreenPinDigit2ChangeScreen>>>();
        constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_PINDIGIT3, LockscreenPinDigitAccessor<3>>, SwitchScreenAction<LockscreenPinDigit3ChangeScreen>>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,                                              SwitchScreenAction<BoardcomputerHardwareSettingsMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
    }
};
} // namespace
