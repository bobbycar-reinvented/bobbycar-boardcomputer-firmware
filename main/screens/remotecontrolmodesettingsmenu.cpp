#include "remotecontrolmodesettingsmenu.h"

// 3rdparty lib includes
#include <actions/popscreenaction.h>
#include <actions/pushscreenaction.h>
#include <changevaluedisplay.h>
#include <menuitem.h>

// local includes
#include "accessors/settingsaccessors.h"
#include "changevaluedisplay_unifiedmodelmode.h"
#include "guihelpers/bobbychangevaluedisplay.h"

namespace bobby {

namespace {
constexpr char TEXT_REMOTEMODESETTINGS[] = "Remote mode settings";
constexpr char TEXT_MODELMODE[] = "Model mode";

using RemoteControlModeModelModeChangeDisplay = espgui::makeComponent<
    BobbyChangeValueDisplay<UnifiedModelMode>,
    espgui::StaticTitle<TEXT_MODELMODE>,
    RemoteControlModeModelModeAccessor,
    espgui::ConfirmActionInterface<espgui::PopScreenAction>,
    espgui::BackActionInterface<espgui::PopScreenAction>
>;
} // namespace

RemoteControlModeSettingsMenu::RemoteControlModeSettingsMenu()
{
    using namespace espgui;

    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_MODELMODE>,          PushScreenAction<RemoteControlModeModelModeChangeDisplay>>>();
}

std::string RemoteControlModeSettingsMenu::title() const
{
    return TEXT_REMOTEMODESETTINGS;
}

void RemoteControlModeSettingsMenu::back()
{
    espgui::popScreen();
}
} // namespace bobby
