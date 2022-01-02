// This menu is disabled because of issues with the new config system. It may be reenabled in the near future.

// ALso reenable in mainmenu!!

/*
#include "presetsmenu.h"

// local includes
#include "actioninterface.h"
#include "actions/multiaction.h"
#include "actions/switchscreenaction.h"
#include "globals.h"
#include "icons/back.h"
#include "mainmenu.h"
#include "menudisplay.h"
#include "presets.h"
#include "settings.h"
#include "utils.h"

namespace {
constexpr char TEXT_PRESETS[] = "Presets";
constexpr char TEXT_DEFAULTEVERYTHING[] = "Default everything";
constexpr char TEXT_DEFAULTLIMITS[] = "Default limits";
constexpr char TEXT_KIDSLIMITS[] = "Kids limits";
constexpr char TEXT_DEFAULTPOTI[] = "Default poti";
constexpr char TEXT_DEFAULTCONTROLLERHARDWARE[] = "Default controller H/W";
constexpr char TEXT_MOSFETSOFFCONTROLLERHARDWARE[] = "MOSFETs off controller H/W";
constexpr char TEXT_SPINNERCONTROLLERHARDWARE[] = "Spinner controller H/W";
constexpr char TEXT_DEFAULTBOARDCOMPUTERHARDWARE[] = "Default boardcomputer H/W";
constexpr char TEXT_DEFAULTDEFAULTMODE[] = "Default defaultMode";
constexpr char TEXT_SINUSOIDALDEFAULTMODE[] = "Sinusoidal defaultMode";
constexpr char TEXT_DEFAULTTEMPOMATMODE[] = "Default tempomatMode";
constexpr char TEXT_DEFAULTLARSMMODE[] = "Default larsmMode";
constexpr char TEXT_STREET[] = "Street";
constexpr char TEXT_SIDEWALK[] = "Sidewalk";
constexpr char TEXT_POLICE[] = "Police";
constexpr char TEXT_RACE[] = "Race";
constexpr char TEXT_BACK[] = "Back";

class ApplyPresetAction : public virtual ActionInterface
{
public:
    void triggered() override { saveSettings(); switchScreen<MainMenu>(); }
};

template<const Settings *preset>
class ApplySettingsPresetAction : public virtual ApplyPresetAction
{
public:
    void triggered() override { settings = *preset; ApplyPresetAction::triggered(); }
};

template<const Settings::Limits *preset>
class ApplyLimitsPresetAction : public virtual ApplyPresetAction
{
public:
    void triggered() override { settings.limits = *preset; ApplyPresetAction::triggered(); }
};

template<const Settings::ControllerHardware *preset>
class ApplyControllerHardwarePresetAction : public virtual ApplyPresetAction
{
public:
    void triggered() override { settings.controllerHardware = *preset; ApplyPresetAction::triggered(); }
};

template<const Settings::BoardcomputerHardware *preset>
class ApplyBoardcomputerHardwarePresetAction : public virtual ApplyPresetAction
{
public:
    void triggered() override { settings.boardcomputerHardware = *preset; ApplyPresetAction::triggered(); }
};

template<const Settings::DefaultMode *preset>
class ApplyDefaultModePresetAction : public virtual ApplyPresetAction
{
public:
    void triggered() override { settings.defaultMode = *preset; ApplyPresetAction::triggered(); }
};

template<const Settings::TempomatMode *preset>
class ApplyTempomatModePresetAction : public virtual ApplyPresetAction
{
public:
    void triggered() override { settings.tempomatMode = *preset; ApplyPresetAction::triggered(); }
};

template<const Settings::LarsmMode *preset>
class ApplyLarsmModePresetAction : public virtual ApplyPresetAction
{
public:
    void triggered() override { settings.larsmMode = *preset; ApplyPresetAction::triggered(); }
};
} // namespace

PresetsMenu::PresetsMenu()
{
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_DEFAULTEVERYTHING>,            MultiAction<ApplySettingsPresetAction<&presets::defaultSettings>, SwitchScreenAction<MainMenu>>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_DEFAULTLIMITS>,                MultiAction<ApplyLimitsPresetAction<&presets::defaultLimits>, SwitchScreenAction<MainMenu>>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_KIDSLIMITS>,                   MultiAction<ApplyLimitsPresetAction<&presets::kidsLimits>, SwitchScreenAction<MainMenu>>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_DEFAULTCONTROLLERHARDWARE>,    MultiAction<ApplyControllerHardwarePresetAction<&presets::defaultControllerHardware>, SwitchScreenAction<MainMenu>>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_MOSFETSOFFCONTROLLERHARDWARE>, MultiAction<ApplyControllerHardwarePresetAction<&presets::mosfetsOffControllerHardware>, SwitchScreenAction<MainMenu>>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_SPINNERCONTROLLERHARDWARE>,    MultiAction<ApplyControllerHardwarePresetAction<&presets::spinnerControllerHardware>, SwitchScreenAction<MainMenu>>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_DEFAULTBOARDCOMPUTERHARDWARE>, MultiAction<ApplyBoardcomputerHardwarePresetAction<&presets::defaultBoardcomputerHardware>, SwitchScreenAction<MainMenu>>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_DEFAULTDEFAULTMODE>,           MultiAction<ApplyDefaultModePresetAction<&presets::defaultDefaultMode>, SwitchScreenAction<MainMenu>>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_SINUSOIDALDEFAULTMODE>,        MultiAction<ApplyDefaultModePresetAction<&presets::sinusoidalDefaultMode>, SwitchScreenAction<MainMenu>>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_DEFAULTTEMPOMATMODE>,          MultiAction<ApplyTempomatModePresetAction<&presets::defaultTempomatMode>, SwitchScreenAction<MainMenu>>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_DEFAULTLARSMMODE>,             MultiAction<ApplyLarsmModePresetAction<&presets::defaultLarsmMode>, SwitchScreenAction<MainMenu>>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,                         SwitchScreenAction<MainMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
}

std::string PresetsMenu::text() const
{
    return TEXT_PRESETS;
}

void PresetsMenu::back()
{
    switchScreen<MainMenu>();
}
*/
