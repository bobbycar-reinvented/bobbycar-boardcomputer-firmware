#include "enablemenu.h"

// 3rdparty lib includes
#include "actions/switchscreenaction.h"
#include "icons/back.h"

// local includes
#include "displays/menus/controllerhardwaresettingsmenu.h"
#include "accessors/settingsaccessors.h"
#include "bobbycheckbox.h"

EnableMenu::EnableMenu()
{
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ENABLEFRONTLEFT>,  BobbyCheckbox, FrontLeftEnabledAccessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ENABLEFRONTRIGHT>, BobbyCheckbox, FrontRightEnabledAccessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ENABLEBACKLEFT>,   BobbyCheckbox, BackLeftEnabledAccessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ENABLEBACKRIGHT>,  BobbyCheckbox, BackRightEnabledAccessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,             SwitchScreenAction<ControllerHardwareSettingsMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
}

void EnableMenu::back()
{
    switchScreen<ControllerHardwareSettingsMenu>();
}
