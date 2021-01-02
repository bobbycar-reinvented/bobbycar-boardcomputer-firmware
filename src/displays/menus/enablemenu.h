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
class EnableMenu :
    public MenuDisplay,
    public StaticText<TEXT_SETENABLED>,
    public BackActionInterface<SwitchScreenAction<ControllerHardwareSettingsMenu>>,
    public ContainerMenuDefinition
{
public:
    EnableMenu()
    {
        constructItem<makeComponent<MenuItem, StaticText<TEXT_ENABLEFRONTLEFT>,  ToggleBoolAction, CheckboxIcon, FrontLeftEnabledAccessor>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_ENABLEFRONTRIGHT>, ToggleBoolAction, CheckboxIcon, FrontRightEnabledAccessor>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_ENABLEBACKLEFT>,   ToggleBoolAction, CheckboxIcon, BackLeftEnabledAccessor>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_ENABLEBACKRIGHT>,  ToggleBoolAction, CheckboxIcon, BackRightEnabledAccessor>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,             SwitchScreenAction<ControllerHardwareSettingsMenu>, StaticMenuItemIcon<&icons::back>>>();
    }
};
} // namespace
