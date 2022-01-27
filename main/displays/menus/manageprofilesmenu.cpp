#include "manageprofilesmenu.h"

// 3rdparty lib includes
#include <icons/back.h>

// local includes
#include "actions/switchscreenaction.h"
#include "mainmenu.h"

namespace {
constexpr char TEXT_MANAGEPROFILESMENU[] = "Manage Profiles Menu";
constexpr char TEXT_BACK[] = "Back";
}

using namespace espgui;

ManageProfilesMenu::ManageProfilesMenu()
{
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>, SwitchScreenAction<MainMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
}

void ManageProfilesMenu::back()
{
    switchScreen<MainMenu>();
}

std::string ManageProfilesMenu::text() const
{
    return TEXT_MANAGEPROFILESMENU;
}
// functions: clear profile, copy profile, move profile
