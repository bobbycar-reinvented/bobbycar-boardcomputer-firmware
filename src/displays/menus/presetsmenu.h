#pragma once

#include "actioninterface.h"
#include "menudisplay.h"
#include "staticmenudefinition.h"
#include "utils.h"
#include "actions/dummyaction.h"
#include "actions/switchscreenaction.h"
#include "icons/back.h"
#include "texts.h"
#include "settings.h"
#include "presets.h"
#include "globals.h"

namespace {
class MainMenu;
}

namespace {
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

class PresetsMenu :
    public MenuDisplay,
    public StaticText<TEXT_PRESETS>,
    public BackActionInterface<SwitchScreenAction<MainMenu>>,
    public StaticMenuDefinition<
        makeComponent<MenuItem, StaticText<TEXT_DEFAULTEVERYTHING>,            ApplySettingsPresetAction<&presets::defaultSettings>>,
        makeComponent<MenuItem, StaticText<TEXT_DEFAULTLIMITS>,                ApplyLimitsPresetAction<&presets::defaultLimits>>,
        makeComponent<MenuItem, StaticText<TEXT_KIDSLIMITS>,                   ApplyLimitsPresetAction<&presets::kidsLimits>>,
        makeComponent<MenuItem, StaticText<TEXT_DEFAULTCONTROLLERHARDWARE>,    ApplyControllerHardwarePresetAction<&presets::defaultControllerHardware>>,
        makeComponent<MenuItem, StaticText<TEXT_MOSFETSOFFCONTROLLERHARDWARE>, ApplyControllerHardwarePresetAction<&presets::mosfetsOffControllerHardware>>,
        makeComponent<MenuItem, StaticText<TEXT_SPINNERCONTROLLERHARDWARE>,    ApplyControllerHardwarePresetAction<&presets::spinnerControllerHardware>>,
        makeComponent<MenuItem, StaticText<TEXT_DEFAULTBOARDCOMPUTERHARDWARE>, ApplyBoardcomputerHardwarePresetAction<&presets::defaultBoardcomputerHardware>>,
        makeComponent<MenuItem, StaticText<TEXT_DEFAULTDEFAULTMODE>,           ApplyDefaultModePresetAction<&presets::defaultDefaultMode>>,
        makeComponent<MenuItem, StaticText<TEXT_SINUSOIDALDEFAULTMODE>,        ApplyDefaultModePresetAction<&presets::sinusoidalDefaultMode>>,
        makeComponent<MenuItem, StaticText<TEXT_DEFAULTTEMPOMATMODE>,          ApplyTempomatModePresetAction<&presets::defaultTempomatMode>>,
        makeComponent<MenuItem, StaticText<TEXT_DEFAULTLARSMMODE>,             ApplyLarsmModePresetAction<&presets::defaultLarsmMode>>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,                         SwitchScreenAction<MainMenu>, StaticMenuItemIcon<&icons::back>>
    >
{};
}
