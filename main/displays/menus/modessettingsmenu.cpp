#include "modessettingsmenu.h"

// 3rdparty lib includes
#include "menuitem.h"
#include "actions/switchscreenaction.h"
#include "icons/back.h"

// local includes
#include "displays/menus/defaultmodesettingsmenu.h"
#include "displays/menus/tempomatmodesettingsmenu.h"
#include "displays/menus/larsmmodesettingsmenu.h"
#include "displays/menus/gametrakmodesettingsmenu.h"
#include "displays/menus/settingsmenu.h"

using namespace espgui;

ModesSettingsMenu::ModesSettingsMenu()
{
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_DEFAULTMODESETTIGNS>,   SwitchScreenAction<DefaultModeSettingsMenu>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_TEMPOMATMODESETTINGS>,  SwitchScreenAction<TempomatModeSettingsMenu>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_LARSMMODESETTINGS>,     SwitchScreenAction<LarsmModeSettingsMenu>>>();
#ifdef FEATURE_GAMETRAK
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_GAMETRAKMODESETTINGS>,  SwitchScreenAction<GametrakModeSettingsMenu>>>();
#endif
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,                  SwitchScreenAction<SettingsMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
}

void ModesSettingsMenu::back()
{
    switchScreen<SettingsMenu>();
}
