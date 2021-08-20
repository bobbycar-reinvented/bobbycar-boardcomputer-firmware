#pragma once

// local includes
#include "menudisplay.h"
#include "utils.h"
#include "menuitem.h"
#include "actions/toggleboolaction.h"
#include "actions/switchscreenaction.h"
#include "checkboxicon.h"
#include "icons/back.h"
#include "texts.h"
#include "accessors/settingsaccessors.h"

// forward declares
namespace {
class ControllerHardwareSettingsMenu;
} // namespace

using namespace espgui;

namespace {
class EnableMenu :
    public MenuDisplay,
    public StaticText<TEXT_SETENABLED>,
    public BackActionInterface<SwitchScreenAction<ControllerHardwareSettingsMenu>>
{
public:
    EnableMenu()
    {
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ENABLEFRONTLEFT>,  ToggleBoolAction, CheckboxIcon, FrontLeftEnabledAccessor>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ENABLEFRONTRIGHT>, ToggleBoolAction, CheckboxIcon, FrontRightEnabledAccessor>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ENABLEBACKLEFT>,   ToggleBoolAction, CheckboxIcon, BackLeftEnabledAccessor>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ENABLEBACKRIGHT>,  ToggleBoolAction, CheckboxIcon, BackRightEnabledAccessor>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,             SwitchScreenAction<ControllerHardwareSettingsMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
    }
};
} // namespace
