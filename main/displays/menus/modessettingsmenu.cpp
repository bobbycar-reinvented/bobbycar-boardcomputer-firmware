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

namespace {
constexpr char TEXT_MODESSETTINGS[] = "Modes settings";
constexpr char TEXT_DEFAULTMODESETTIGNS[] = "Default mode settings";
constexpr char TEXT_TEMPOMATMODESETTINGS[] = "Tempomat mode settings";
constexpr char TEXT_LARSMMODESETTINGS[] = "Larsm mode settings";
constexpr char TEXT_GAMETRAKMODESETTINGS[] = "Gametrak mode settings";
constexpr char TEXT_BACK[] = "Back";
} // namespace

ModesSettingsMenu::ModesSettingsMenu()
{
    using namespace espgui;
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_DEFAULTMODESETTIGNS>,   SwitchScreenAction<DefaultModeSettingsMenu>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_TEMPOMATMODESETTINGS>,  SwitchScreenAction<TempomatModeSettingsMenu>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_LARSMMODESETTINGS>,     SwitchScreenAction<LarsmModeSettingsMenu>>>();
#ifdef FEATURE_GAMETRAK
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_GAMETRAKMODESETTINGS>,  SwitchScreenAction<GametrakModeSettingsMenu>>>();
#endif
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,                  SwitchScreenAction<SettingsMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
}

std::string ModesSettingsMenu::text() const
{
    return TEXT_MODESSETTINGS;
}

void ModesSettingsMenu::back()
{
    espgui::switchScreen<SettingsMenu>();
}
