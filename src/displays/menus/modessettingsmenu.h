#pragma once

#include "menudisplay.h"
#include "staticmenudefinition.h"
#include "menuitem.h"
#include "actions/switchscreenaction.h"
#include "icons/back.h"
#include "texts.h"

namespace {
class DefaultModeSettingsMenu;
class TempomatModeSettingsMenu;
class LarsmModeSettingsMenu;
class SettingsMenu;
}

namespace {
class ModesSettingsMenu :
    public MenuDisplay,
    public StaticText<TEXT_MODESSETTINGS>,
    public BackActionInterface<SwitchScreenAction<SettingsMenu>>,
    public StaticMenuDefinition<
        makeComponent<MenuItem, StaticText<TEXT_DEFAULTMODESETTIGNS>,   SwitchScreenAction<DefaultModeSettingsMenu>>,
        makeComponent<MenuItem, StaticText<TEXT_TEMPOMATMODESETTINGS>,  SwitchScreenAction<TempomatModeSettingsMenu>>,
        makeComponent<MenuItem, StaticText<TEXT_LARSMMODESETTINGS>,     SwitchScreenAction<LarsmModeSettingsMenu>>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,                  SwitchScreenAction<SettingsMenu>, StaticMenuItemIcon<&icons::back>>
    >
{};
}
