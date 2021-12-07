#include "profilesmenu.h"

// local includes
#include "actions/switchprofileaction.h"
#include "actions/switchscreenaction.h"
#include "displays/menus/mainmenu.h"
#include "icons/back.h"
#include "menudisplay.h"
#include "texts.h"

ProfilesMenu::ProfilesMenu()
{
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_PROFILE0>, SwitchProfileAction<0>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_PROFILE1>, SwitchProfileAction<1>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_PROFILE2>, SwitchProfileAction<2>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_PROFILE3>, SwitchProfileAction<3>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,     SwitchScreenAction<MainMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
}

void ProfilesMenu::back()
{
    switchScreen<MainMenu>();
}
