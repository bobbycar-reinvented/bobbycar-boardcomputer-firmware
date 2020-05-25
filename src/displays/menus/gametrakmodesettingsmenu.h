#pragma once

#include "menudisplay.h"
#include "staticmenudefinition.h"
#include "utils.h"
#include "menuitem.h"
#include "actions/switchscreenaction.h"
#include "icons/back.h"
#include "texts.h"

namespace {
class ModesSettingsMenu;
}

namespace {
#ifdef FEATURE_GAMETRAK
class GametrakModeSettingsMenu :
    public MenuDisplay,
    public StaticText<TEXT_GAMETRAKMODESETTINGS>,
    public BackActionInterface<SwitchScreenAction<ModesSettingsMenu>>,
    public StaticMenuDefinition<
        makeComponent<MenuItem, StaticText<TEXT_BACK>, SwitchScreenAction<ModesSettingsMenu>, StaticMenuItemIcon<&icons::back>>
    >
{};
#endif
}
