#pragma once

// local includes
#include "menudisplay.h"
#include "containermenudefinition.h"
#include "actions/switchprofileaction.h"
#include "actions/switchscreenaction.h"
#include "icons/back.h"
#include "texts.h"

// forward declares
namespace {
class MainMenu;
} // namespace

namespace {
class ProfilesMenu :
    public MenuDisplay,
    public StaticText<TEXT_PROFILES>,
    public BackActionInterface<SwitchScreenAction<MainMenu>>,
    public ContainerMenuDefinition
{
public:
    ProfilesMenu()
    {
        constructItem<makeComponent<MenuItem, StaticText<TEXT_PROFILE0>, SwitchProfileAction<0>>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_PROFILE1>, SwitchProfileAction<1>>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_PROFILE2>, SwitchProfileAction<2>>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_PROFILE3>, SwitchProfileAction<3>>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,     SwitchScreenAction<MainMenu>, StaticMenuItemIcon<&icons::back>>>();
    }
};
} // namespace
