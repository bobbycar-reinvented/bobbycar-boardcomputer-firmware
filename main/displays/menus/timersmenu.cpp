#include "timersmenu.h"

// 3rdparty lib includes
#include "actions/switchscreenaction.h"
#include "changevaluedisplay.h"
#include "icons/back.h"

// local includes
#include "displays/bobbychangevaluedisplay.h"
#include "accessors/settingsaccessors.h"
#include "displays/menus/boardcomputerhardwaresettingsmenu.h"
#include "texts.h"

namespace {
using StatsUpdateRateChangeDisplay = espgui::makeComponent<
    BobbyChangeValueDisplay<int16_t>,
    espgui::StaticText<TEXT_STATSUPDATERATE>,
    StatsUpdateRateAccessor,
    espgui::BackActionInterface<espgui::SwitchScreenAction<TimersMenu>>,
    espgui::SwitchScreenAction<TimersMenu>
>;
}

TimersMenu::TimersMenu()
{
    using namespace espgui;
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_STATSUPDATERATE>,   SwitchScreenAction<StatsUpdateRateChangeDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,              SwitchScreenAction<BoardcomputerHardwareSettingsMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
}

void TimersMenu::back()
{
    espgui::switchScreen<BoardcomputerHardwareSettingsMenu>();
}
