#pragma once

// local includes
#include "menudisplay.h"
#include "containermenudefinition.h"
#include "utils.h"
#include "changevaluedisplay.h"
#include "actions/dummyaction.h"
#include "actions/switchscreenaction.h"
#include "actions/toggleboolaction.h"
#include "icons/back.h"
#include "checkboxicon.h"
#include "texts.h"
#include "settingsaccessors.h"

// forward declares
namespace {
class BoardcomputerHardwareSettingsMenu;
class CalibrateDisplay;
class GametrakCalibrateDisplay;
class TimersMenu;
class SettingsMenu;
} // namespace

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
    public ContainerMenuDefinition
{
public:
    BoardcomputerHardwareSettingsMenu()
    {
        constructItem<makeComponent<MenuItem, GasText,                             DisabledColor, StaticFont<2>, DummyAction>>();
        constructItem<makeComponent<MenuItem, BremsText,                           DisabledColor, StaticFont<2>, DummyAction>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_CALIBRATE>,          SwitchScreenAction<CalibrateDisplay>>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_SETSAMPLECOUNT>,     SwitchScreenAction<SampleCountChangeScreen>>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_SETGASMIN>,          SwitchScreenAction<GasMinChangeScreen>>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_SETGASMAX>,          SwitchScreenAction<GasMaxChangeScreen>>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_SETBREMSMIN>,        SwitchScreenAction<BremsMinChangeScreen>>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_SETBREMSMAX>,        SwitchScreenAction<BremsMaxChangeScreen>>>();
#if defined(FEATURE_DPAD) || defined(FEATURE_DPAD_3WIRESW) || defined(FEATURE_DPAD_5WIRESW)
        constructItem<makeComponent<MenuItem, StaticText<TEXT_SETDPADDEBOUNCE>,    SwitchScreenAction<DPadDebounceChangeScreen>>>();
#endif
#ifdef FEATURE_GAMETRAK
        constructItem<makeComponent<MenuItem, StaticText<nullptr>,                 DummyAction>,
        constructItem<makeComponent<MenuItem, GametrakXText,                       DisabledColor, StaticFont<2>, DummyAction>>();
        constructItem<makeComponent<MenuItem, GametrakYText,                       DisabledColor, StaticFont<2>, DummyAction>>();
        constructItem<makeComponent<MenuItem, GametrakDistText,                    DisabledColor, StaticFont<2>, DummyAction>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_GAMETRAKCALIBRATE>,  SwitchScreenAction<GametrakCalibrateDisplay>>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_SETGAMETRAKXMIN>,    SwitchScreenAction<GametrakXMinChangeScreen>>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_SETGAMETRAKXMAX>,    SwitchScreenAction<GametrakXMaxChangeScreen>>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_SETGAMETRAKYMIN>,    SwitchScreenAction<GametrakYMinChangeScreen>>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_SETGAMETRAKYMAX>,    SwitchScreenAction<GametrakYMaxChangeScreen>>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_SETGAMETRAKDISTMIN>, SwitchScreenAction<GametrakDistMinChangeScreen>>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_SETGAMETRAKDISTMAX>, SwitchScreenAction<GametrakDistMaxChangeScreen>>>();
#endif
        constructItem<makeComponent<MenuItem, StaticText<nullptr>,                 DummyAction>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_SWAPSCREENBYTES>,    ToggleBoolAction, CheckboxIcon, SwapScreenBytesAccessor>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_TIMERS>,             SwitchScreenAction<TimersMenu>>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,               SwitchScreenAction<SettingsMenu>, StaticMenuItemIcon<&icons::back>>>();
    }
};
} // namespace
