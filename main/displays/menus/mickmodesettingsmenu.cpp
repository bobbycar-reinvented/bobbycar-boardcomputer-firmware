#include "mickmodesettingsmenu.h"

// 3rdparty lib includes
#include "changevaluedisplay.h"
#include "menuitem.h"
#include "actions/switchscreenaction.h"
#include "icons/back.h"

// local includes
#include "displays/bobbychangevaluedisplay.h"
#include "utils.h"
#include "changevaluedisplay_unifiedmodelmode.h"
#include "accessors/settingsaccessors.h"
#include "displays/menus/modessettingsmenu.h"

namespace {
constexpr char TEXT_MICKMODESETTINGS[] = "Mick mode settings";
constexpr char TEXT_MODELMODE[] = "Model mode";
constexpr char TEXT_MICKMODE_SMOOTHING[] = "Tau in ms";
constexpr char TEXT_BACK[] = "Back";

using MickModeModelModeChangeDisplay = espgui::makeComponent<
    BobbyChangeValueDisplay<UnifiedModelMode>,
    espgui::StaticText<TEXT_MODELMODE>,
    MickModeModelModeAccessor,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<MickModeSettingsMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<MickModeSettingsMenu>>
>;
using MickModeSmoothingChangeDisplay = espgui::makeComponent<
    BobbyChangeValueDisplay<uint16_t>,
    espgui::StaticText<TEXT_MICKMODE_SMOOTHING>,
    MickModeSmoothingAccessor,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<MickModeSettingsMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<MickModeSettingsMenu>>
>;
} // namespace

using namespace espgui;

MickModeSettingsMenu::MickModeSettingsMenu()
{
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_MODELMODE>,          SwitchScreenAction<MickModeModelModeChangeDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_MICKMODE_SMOOTHING>, SwitchScreenAction<MickModeSmoothingChangeDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,               SwitchScreenAction<ModesSettingsMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
}

std::string MickModeSettingsMenu::text() const
{
    return TEXT_MICKMODESETTINGS;
}

void MickModeSettingsMenu::back()
{
    switchScreen<ModesSettingsMenu>();
}
