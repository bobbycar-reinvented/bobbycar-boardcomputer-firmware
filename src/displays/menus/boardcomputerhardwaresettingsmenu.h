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
class GametrakCalibrateDisplay;
class TimersMenu;
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

#if defined(FEATURE_DPAD) || defined(FEATURE_DPAD_3WIRESW) || defined(FEATURE_DPAD_5WIRESW)
using DPadDebounceChangeScreen = makeComponent<
    ChangeValueDisplay<uint8_t>,
    StaticText<TEXT_SETDPADDEBOUNCE>,
    DPadDebounceAccessor,
    BackActionInterface<SwitchScreenAction<BoardcomputerHardwareSettingsMenu>>,
    SwitchScreenAction<BoardcomputerHardwareSettingsMenu>
>;
#endif

#ifdef FEATURE_GAMETRAK
struct GametrakXText : public virtual TextInterface {
public:
    String text() const override { return String{"gametrakX: "} + raw_gametrakX + ": " + gametrakX; }
};
struct GametrakYText : public virtual TextInterface {
public:
    String text() const override { return String{"gametrakY: "} + raw_gametrakY + ": " + gametrakY; }
};
struct GametrakDistText : public virtual TextInterface {
public:
    String text() const override { return String{"gametrakDist: "} + raw_gametrakDist + ": " + gametrakDist; }
};

using GametrakXMinChangeScreen = makeComponent<
    ChangeValueDisplay<int16_t>,
    StaticText<TEXT_SETGAMETRAKXMIN>,
    GametrakXMinAccessor,
    BackActionInterface<SwitchScreenAction<BoardcomputerHardwareSettingsMenu>>,
    SwitchScreenAction<BoardcomputerHardwareSettingsMenu>
>;
using GametrakXMaxChangeScreen = makeComponent<
    ChangeValueDisplay<int16_t>,
    StaticText<TEXT_SETGAMETRAKXMAX>,
    GametrakXMaxAccessor,
    BackActionInterface<SwitchScreenAction<BoardcomputerHardwareSettingsMenu>>,
    SwitchScreenAction<BoardcomputerHardwareSettingsMenu>
>;
using GametrakYMinChangeScreen = makeComponent<
    ChangeValueDisplay<int16_t>,
    StaticText<TEXT_SETGAMETRAKYMIN>,
    GametrakYMinAccessor,
    BackActionInterface<SwitchScreenAction<BoardcomputerHardwareSettingsMenu>>,
    SwitchScreenAction<BoardcomputerHardwareSettingsMenu>
>;
using GametrakYMaxChangeScreen = makeComponent<
    ChangeValueDisplay<int16_t>,
    StaticText<TEXT_SETGAMETRAKYMAX>,
    GametrakYMaxAccessor,
    BackActionInterface<SwitchScreenAction<BoardcomputerHardwareSettingsMenu>>,
    SwitchScreenAction<BoardcomputerHardwareSettingsMenu>
>;
using GametrakDistMinChangeScreen = makeComponent<
    ChangeValueDisplay<int16_t>,
    StaticText<TEXT_SETGAMETRAKDISTMIN>,
    GametrakDistMinAccessor,
    BackActionInterface<SwitchScreenAction<BoardcomputerHardwareSettingsMenu>>,
    SwitchScreenAction<BoardcomputerHardwareSettingsMenu>
>;
using GametrakDistMaxChangeScreen = makeComponent<
    ChangeValueDisplay<int16_t>,
    StaticText<TEXT_SETGAMETRAKDISTMAX>,
    GametrakDistMaxAccessor,
    BackActionInterface<SwitchScreenAction<BoardcomputerHardwareSettingsMenu>>,
    SwitchScreenAction<BoardcomputerHardwareSettingsMenu>
>;
#endif

class BoardcomputerHardwareSettingsMenu :
    public MenuDisplay,
    public StaticText<TEXT_BOARDCOMPUTERHARDWARESETTINGS>,
    public BackActionInterface<SwitchScreenAction<SettingsMenu>>,
    public StaticMenuDefinition<
        makeComponent<MenuItem, GasText,                             DisabledColor, StaticFont<2>, DummyAction>,
        makeComponent<MenuItem, BremsText,                           DisabledColor, StaticFont<2>, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_CALIBRATE>,          SwitchScreenAction<CalibrateDisplay>>,
        makeComponent<MenuItem, StaticText<TEXT_SETSAMPLECOUNT>,     SwitchScreenAction<SampleCountChangeScreen>>,
        makeComponent<MenuItem, StaticText<TEXT_SETGASMIN>,          SwitchScreenAction<GasMinChangeScreen>>,
        makeComponent<MenuItem, StaticText<TEXT_SETGASMAX>,          SwitchScreenAction<GasMaxChangeScreen>>,
        makeComponent<MenuItem, StaticText<TEXT_SETBREMSMIN>,        SwitchScreenAction<BremsMinChangeScreen>>,
        makeComponent<MenuItem, StaticText<TEXT_SETBREMSMAX>,        SwitchScreenAction<BremsMaxChangeScreen>>,
#if defined(FEATURE_DPAD) || defined(FEATURE_DPAD_3WIRESW) || defined(FEATURE_DPAD_5WIRESW)
        makeComponent<MenuItem, StaticText<TEXT_SETDPADDEBOUNCE>,    SwitchScreenAction<DPadDebounceChangeScreen>>,
#endif
#ifdef FEATURE_GAMETRAK
        makeComponent<MenuItem, StaticText<nullptr>,                 DummyAction>,
        makeComponent<MenuItem, GametrakXText,                       DisabledColor, StaticFont<2>, DummyAction>,
        makeComponent<MenuItem, GametrakYText,                       DisabledColor, StaticFont<2>, DummyAction>,
        makeComponent<MenuItem, GametrakDistText,                    DisabledColor, StaticFont<2>, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_GAMETRAKCALIBRATE>,  SwitchScreenAction<GametrakCalibrateDisplay>>,
        makeComponent<MenuItem, StaticText<TEXT_SETGAMETRAKXMIN>,    SwitchScreenAction<GametrakXMinChangeScreen>>,
        makeComponent<MenuItem, StaticText<TEXT_SETGAMETRAKXMAX>,    SwitchScreenAction<GametrakXMaxChangeScreen>>,
        makeComponent<MenuItem, StaticText<TEXT_SETGAMETRAKYMIN>,    SwitchScreenAction<GametrakYMinChangeScreen>>,
        makeComponent<MenuItem, StaticText<TEXT_SETGAMETRAKYMAX>,    SwitchScreenAction<GametrakYMaxChangeScreen>>,
        makeComponent<MenuItem, StaticText<TEXT_SETGAMETRAKDISTMIN>, SwitchScreenAction<GametrakDistMinChangeScreen>>,
        makeComponent<MenuItem, StaticText<TEXT_SETGAMETRAKDISTMAX>, SwitchScreenAction<GametrakDistMaxChangeScreen>>,
#endif
        makeComponent<MenuItem, StaticText<nullptr>,                 DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_SWAPSCREENBYTES>,    ToggleBoolAction, CheckboxIcon, SwapScreenBytesAccessor>,
        makeComponent<MenuItem, StaticText<TEXT_TIMERS>,             SwitchScreenAction<TimersMenu>>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,               SwitchScreenAction<SettingsMenu>, StaticMenuItemIcon<&icons::back>>
    >
{};
}
