#pragma once

// local includes
#include "menudisplay.h"
#include "containermenudefinition.h"
#include "menuitem.h"
#include "actions/switchscreenaction.h"
#include "icons/back.h"
#include "texts.h"

// forward declares
namespace {
class DefaultModeSettingsMenu;
class TempomatModeSettingsMenu;
class LarsmModeSettingsMenu;
class GametrakModeSettingsMenu;
class SettingsMenu;
} // namespace

namespace {
class ModesSettingsMenu :
    public MenuDisplay,
    public StaticText<TEXT_MODESSETTINGS>,
    public BackActionInterface<SwitchScreenAction<SettingsMenu>>,
    public ContainerMenuDefinition
{
public:
    ModesSettingsMenu()
    {
        constructItem<makeComponent<MenuItem, StaticText<TEXT_DEFAULTMODESETTIGNS>,   SwitchScreenAction<DefaultModeSettingsMenu>>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_TEMPOMATMODESETTINGS>,  SwitchScreenAction<TempomatModeSettingsMenu>>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_LARSMMODESETTINGS>,     SwitchScreenAction<LarsmModeSettingsMenu>>>();
#ifdef FEATURE_GAMETRAK
        constructItem<makeComponent<MenuItem, StaticText<TEXT_GAMETRAKMODESETTINGS>,  SwitchScreenAction<GametrakModeSettingsMenu>>>();
#endif
        constructItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,                  SwitchScreenAction<SettingsMenu>, StaticMenuItemIcon<&icons::back>>>();
    }
};
} // namespace
