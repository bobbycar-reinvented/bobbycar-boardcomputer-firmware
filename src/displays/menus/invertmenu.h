#pragma once

// local includes
#include "menudisplay.h"
#include "containermenudefinition.h"
#include "utils.h"
#include "menuitem.h"
#include "actions/toggleboolaction.h"
#include "actions/switchscreenaction.h"
#include "checkboxicon.h"
#include "icons/back.h"
#include "texts.h"
#include "settingsaccessors.h"

// forward declares
namespace {
class ControllerHardwareSettingsMenu;
} // namespace

namespace {
class InvertMenu :
    public MenuDisplay,
    public StaticText<TEXT_SETINVERTED>,
    public BackActionInterface<SwitchScreenAction<ControllerHardwareSettingsMenu>>,
    public ContainerMenuDefinition
{
public:
    InvertMenu()
    {
        constructItem<makeComponent<MenuItem, StaticText<TEXT_INVERTFRONTLEFT>,  ToggleBoolAction, CheckboxIcon, FrontLeftInvertedAccessor>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_INVERTFRONTRIGHT>, ToggleBoolAction, CheckboxIcon, FrontRightInvertedAccessor>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_INVERTBACKLEFT>,   ToggleBoolAction, CheckboxIcon, BackLeftInvertedAccessor>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_INVERTBACKRIGHT>,  ToggleBoolAction, CheckboxIcon, BackRightInvertedAccessor>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,             SwitchScreenAction<ControllerHardwareSettingsMenu>, StaticMenuItemIcon<&icons::back>>>();
    }
};
} // namespace
