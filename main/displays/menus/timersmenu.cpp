#include "timersmenu.h"

// 3rdparty lib includes
#include "actions/switchscreenaction.h"
#include "changevaluedisplay.h"
#include "icons/back.h"

// local includes
#include "displays/bobbychangevaluedisplay.h"
#include "accessors/settingsaccessors.h"
#include "displays/menus/boardcomputerhardwaresettingsmenu.h"

namespace {
constexpr char TEXT_TIMERS[] = "Timers";
constexpr char TEXT_STATSUPDATERATE[] = "Stats update rate";
constexpr char TEXT_BACK[] = "Back";

using StatsUpdateRateChangeDisplay = espgui::makeComponent<
    BobbyChangeValueDisplay<int16_t>,
    espgui::StaticText<TEXT_STATSUPDATERATE>,
    StatsUpdateRateAccessor,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<TimersMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<TimersMenu>>
>;
} // namespace

TimersMenu::TimersMenu()
{
    using namespace espgui;
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_STATSUPDATERATE>,   SwitchScreenAction<StatsUpdateRateChangeDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,              SwitchScreenAction<BoardcomputerHardwareSettingsMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
}

std::string TimersMenu::text() const
{
    return TEXT_TIMERS;
}

void TimersMenu::back()
{
    espgui::switchScreen<BoardcomputerHardwareSettingsMenu>();
}
