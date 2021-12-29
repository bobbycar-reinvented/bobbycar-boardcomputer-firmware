#include "invertmenu.h"

// 3rdparty lib includes
#include "actions/switchscreenaction.h"
#include "icons/back.h"

// local includes
#include "accessors/settingsaccessors.h"
#include "displays/menus/controllerhardwaresettingsmenu.h"
#include "bobbycheckbox.h"

InvertMenu::InvertMenu()
{
    using namespace espgui;
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_INVERTFRONTLEFT>,  BobbyCheckbox, FrontLeftInvertedAccessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_INVERTFRONTRIGHT>, BobbyCheckbox, FrontRightInvertedAccessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_INVERTBACKLEFT>,   BobbyCheckbox, BackLeftInvertedAccessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_INVERTBACKRIGHT>,  BobbyCheckbox, BackRightInvertedAccessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,             SwitchScreenAction<ControllerHardwareSettingsMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
}


void InvertMenu::back()
{
    espgui::switchScreen<ControllerHardwareSettingsMenu>();
}
