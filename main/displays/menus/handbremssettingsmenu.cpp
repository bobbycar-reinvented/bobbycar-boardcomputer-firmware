#include "handbremssettingsmenu.h"

// 3rd party libs
#include <fmt/core.h>
#include <actions/switchscreenaction.h>
#include <actions/toggleboolaction.h>
#include <changevaluedisplay.h>
#include <checkboxicon.h>
#include <icons/back.h>
#include <textwithvaluehelper.h>

// local includes
#include "displays/bobbychangevaluedisplay.h"
#include "accessors/settingsaccessors.h"
#include "changevaluedisplay_handbremsmode.h"
#include "displays/menus/defaultmodesettingsmenu.h"
#include "texts.h"

namespace {
using HandBremsTriggerTimeoutChangeValueDisplay = espgui::makeComponent<
    BobbyChangeValueDisplay<uint16_t>,
    espgui::StaticText<TEXT_HANDBREMSE_TRIGGERTIMEOUT>,
    HandbremsTimeoutAccessor,
    espgui::BackActionInterface<espgui::SwitchScreenAction<HandbremsSettingsMenu>>,
    espgui::SwitchScreenAction<HandbremsSettingsMenu>
>;
using HandBremsModeChangeValueDisplay = espgui::makeComponent<
    BobbyChangeValueDisplay<HandbremseMode>,
    espgui::StaticText<TEXT_HANDBREMSE_MODE>,
    HandbremsModeAccessor,
    espgui::BackActionInterface<espgui::SwitchScreenAction<HandbremsSettingsMenu>>,
    espgui::SwitchScreenAction<HandbremsSettingsMenu>
>;
class HandBremsModeText : public virtual espgui::TextInterface
{
public:
    std::string text() const override
    {
        return fmt::format("Mode: &2{}", toString(settings.handbremse.mode));
    }
};
}

HandbremsSettingsMenu::HandbremsSettingsMenu()
{
    using namespace espgui;
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_HANDBREMSE_ENABLE>, ToggleBoolAction, CheckboxIcon, HandbremsEnabledAccessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_HANDBREMSE_AUTOMATIC>, ToggleBoolAction, CheckboxIcon, HandbremsAutomaticAccessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_HANDBREMSE_VISUALIZE>, ToggleBoolAction, CheckboxIcon, HandbremsVisualizeAccessor>>();
    constructMenuItem<makeComponent<MenuItem, HandBremsModeText,    SwitchScreenAction<HandBremsModeChangeValueDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_HANDBREMSE_TRIGGERTIMEOUT, HandbremsTimeoutAccessor>, SwitchScreenAction<HandBremsTriggerTimeoutChangeValueDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>, SwitchScreenAction<DefaultModeSettingsMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
}

void HandbremsSettingsMenu::back()
{
    espgui::switchScreen<DefaultModeSettingsMenu>();
}
