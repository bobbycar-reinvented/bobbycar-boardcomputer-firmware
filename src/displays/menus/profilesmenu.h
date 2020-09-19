#pragma once

#include "menudisplay.h"
#include "staticmenudefinition.h"
#include "actions/switchprofileaction.h"
#include "actions/switchscreenaction.h"
#include "icons/back.h"
#include "texts.h"

namespace {
class MainMenu;
}

namespace {
class ProfilesMenu :
        public MenuDisplay,
        public StaticText<TEXT_PROFILES>,
        public BackActionInterface<SwitchScreenAction<MainMenu>>,
        public StaticMenuDefinition<
            makeComponent<MenuItem, StaticText<TEXT_PROFILE0>, SwitchProfileAction<0>>,
            makeComponent<MenuItem, StaticText<TEXT_PROFILE1>, SwitchProfileAction<1>>,
            makeComponent<MenuItem, StaticText<TEXT_PROFILE2>, SwitchProfileAction<2>>,
            makeComponent<MenuItem, StaticText<TEXT_PROFILE3>, SwitchProfileAction<3>>,
            makeComponent<MenuItem, StaticText<TEXT_BACK>,     SwitchScreenAction<MainMenu>, StaticMenuItemIcon<&icons::back>>
        >
{};
}
