#pragma once

#include "menudisplay.h"
#include "staticmenudefinition.h"
#include "utils.h"
#include "changevaluedisplay.h"
#include "actions/dummyaction.h"
#include "actions/switchscreenaction.h"
#include "actions/toggleboolaction.h"
#include "icons/back.h"
#include "checkboxicon.h"
#include "texts.h"
#include "settingsaccessors.h"

namespace {
class BoardcomputerHardwareSettingsMenu;
class CalibrateDisplay;
class SettingsMenu;
}

namespace {
struct GasText : public virtual TextInterface {
public:
    String text() const override { return String{"gas: "} + raw_gas + ": " + gas; }
};
struct BremsText : public virtual TextInterface {
public:
    String text() const override { return String{"brems: "} + raw_brems + ": " + brems; }
};

using SampleCountChangeScreen = makeComponent<
    ChangeValueDisplay<int16_t>,
    StaticText<TEXT_SETSAMPLECOUNT>,
    SampleCountAccessor,
    BackActionInterface<SwitchScreenAction<BoardcomputerHardwareSettingsMenu>>,
    SwitchScreenAction<BoardcomputerHardwareSettingsMenu>
>;
using GasMinChangeScreen = makeComponent<
    ChangeValueDisplay<int16_t>,
    StaticText<TEXT_SETGASMIN>,
    GasMinAccessor,
    BackActionInterface<SwitchScreenAction<BoardcomputerHardwareSettingsMenu>>,
    SwitchScreenAction<BoardcomputerHardwareSettingsMenu>
>;
using GasMaxChangeScreen = makeComponent<
    ChangeValueDisplay<int16_t>,
    StaticText<TEXT_SETGASMAX>,
    GasMaxAccessor,
    BackActionInterface<SwitchScreenAction<BoardcomputerHardwareSettingsMenu>>,
    SwitchScreenAction<BoardcomputerHardwareSettingsMenu>
>;
using BremsMinChangeScreen = makeComponent<
    ChangeValueDisplay<int16_t>,
    StaticText<TEXT_SETBREMSMIN>,
    BremsMinAccessor,
    BackActionInterface<SwitchScreenAction<BoardcomputerHardwareSettingsMenu>>,
    SwitchScreenAction<BoardcomputerHardwareSettingsMenu>
>;
using BremsMaxChangeScreen = makeComponent<
    ChangeValueDisplay<int16_t>,
    StaticText<TEXT_SETBREMSMAX>,
    BremsMaxAccessor,
    BackActionInterface<SwitchScreenAction<BoardcomputerHardwareSettingsMenu>>,
    SwitchScreenAction<BoardcomputerHardwareSettingsMenu>
>;

class BoardcomputerHardwareSettingsMenu :
    public MenuDisplay,
    public StaticText<TEXT_BOARDCOMPUTERHARDWARESETTINGS>,
    public BackActionInterface<SwitchScreenAction<SettingsMenu>>,
    public StaticMenuDefinition<
        makeComponent<MenuItem, GasText,                         DisabledColor, StaticFont<2>, DummyAction>,
        makeComponent<MenuItem, BremsText,                       DisabledColor, StaticFont<2>, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_CALIBRATE>,      SwitchScreenAction<CalibrateDisplay>>,
        makeComponent<MenuItem, StaticText<TEXT_SETSAMPLECOUNT>, SwitchScreenAction<SampleCountChangeScreen>>,
        makeComponent<MenuItem, StaticText<TEXT_SETGASMIN>,      SwitchScreenAction<GasMinChangeScreen>>,
        makeComponent<MenuItem, StaticText<TEXT_SETGASMAX>,      SwitchScreenAction<GasMaxChangeScreen>>,
        makeComponent<MenuItem, StaticText<TEXT_SETBREMSMIN>,    SwitchScreenAction<BremsMinChangeScreen>>,
        makeComponent<MenuItem, StaticText<TEXT_SETBREMSMAX>,    SwitchScreenAction<BremsMaxChangeScreen>>,
        makeComponent<MenuItem, StaticText<TEXT_SWAPSCREENBYTES>, ToggleBoolAction, CheckboxIcon, SwapScreenBytesAccessor>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,           SwitchScreenAction<SettingsMenu>, StaticMenuItemIcon<&icons::back>>
    >
{};
}
