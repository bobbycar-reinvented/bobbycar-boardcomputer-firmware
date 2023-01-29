#include "larsmmodesettingsmenu.h"

// 3rdparty lib includes
#include <changevaluedisplay.h>
#include <menuitem.h>
#include <actions/pushscreenaction.h>
#include <actions/popscreenaction.h>

// local includes
#include "accessors/settingsaccessors.h"
#include "changevaluedisplay_larsmmode_mode.h"
#include "changevaluedisplay_unifiedmodelmode.h"
#include "guihelpers/bobbychangevaluedisplay.h"
#include "icons/back.h"
#include "utils.h"

namespace bobby {

namespace {
constexpr char TEXT_LARSMMODESETTINGS[] = "Larsm mode settings";
constexpr char TEXT_MODELMODE[] = "Model mode";
constexpr char TEXT_SETMODE[] = "Set mode";
constexpr char TEXT_SETITERATIONS[] = "Set iterations";
constexpr char TEXT_BACK[] = "Back";

using LarsmModeModelModeChangeDisplay = espgui::makeComponent<
    BobbyChangeValueDisplay<UnifiedModelMode>,
    espgui::StaticTitle<TEXT_MODELMODE>,
    LarsmModeModelModeAccessor,
    espgui::ConfirmActionInterface<espgui::PopScreenAction>,
    espgui::BackActionInterface<espgui::PopScreenAction>
>;
using LarsmModeModeChangeDisplay = espgui::makeComponent<
    BobbyChangeValueDisplay<LarsmModeMode>,
    espgui::StaticTitle<TEXT_SETMODE>,
    LarsmModeModeAccessor,
    espgui::ConfirmActionInterface<espgui::PopScreenAction>,
    espgui::BackActionInterface<espgui::PopScreenAction>
>;
using LarsmModeIterationsChangeDisplay = espgui::makeComponent<
    BobbyChangeValueDisplay<uint8_t>,
    espgui::StaticTitle<TEXT_SETITERATIONS>,
    LarsmModeIterationsAccessor,
    espgui::ConfirmActionInterface<espgui::PopScreenAction>,
    espgui::BackActionInterface<espgui::PopScreenAction>
>;
} // namespace

using namespace espgui;

LarsmModeSettingsMenu::LarsmModeSettingsMenu()
{
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_MODELMODE>,     PushScreenAction<LarsmModeModelModeChangeDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_SETMODE>,       PushScreenAction<LarsmModeModeChangeDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_SETITERATIONS>, PushScreenAction<LarsmModeIterationsChangeDisplay>>>();
}

std::string LarsmModeSettingsMenu::title() const
{
    return TEXT_LARSMMODESETTINGS;
}

void LarsmModeSettingsMenu::back()
{
    popScreen();
}

} // namespace bobby
