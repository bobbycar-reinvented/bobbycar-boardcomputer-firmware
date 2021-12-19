#include "timersmenu.h"

// local includes
#include "accessors/settingsaccessors.h"
#include "actions/switchscreenaction.h"
#include "changevaluedisplay.h"
#include "displays/menus/boardcomputerhardwaresettingsmenu.h"
#include "icons/back.h"
#include "texts.h"

using namespace espgui;

namespace {
using ModeUpdateRateChangeDisplay = makeComponent<
    ChangeValueDisplay<int16_t>,
    StaticText<TEXT_MODEUPDATERATE>,
    ModeUpdateRateAccessor,
    BackActionInterface<SwitchScreenAction<TimersMenu>>,
    SwitchScreenAction<TimersMenu>
>;

using StatsUpdateRateChangeDisplay = makeComponent<
    ChangeValueDisplay<int16_t>,
    StaticText<TEXT_STATSUPDATERATE>,
    StatsUpdateRateAccessor,
    BackActionInterface<SwitchScreenAction<TimersMenu>>,
    SwitchScreenAction<TimersMenu>
>;

using DisplayUpdateRateChangeDisplay = makeComponent<
    ChangeValueDisplay<int16_t>,
    StaticText<TEXT_DISPLAYUPDATERATE>,
    DisplayUpdateRateAccessor,
    BackActionInterface<SwitchScreenAction<TimersMenu>>,
    SwitchScreenAction<TimersMenu>
>;

using DisplayRedrawRateChangeDisplay = makeComponent<
    ChangeValueDisplay<int16_t>,
    StaticText<TEXT_DISPLAYREDRAWRATE>,
    DisplayRedrawRateAccessor,
    BackActionInterface<SwitchScreenAction<TimersMenu>>,
    SwitchScreenAction<TimersMenu>
>;
}

TimersMenu::TimersMenu()
{
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_MODEUPDATERATE>,    SwitchScreenAction<ModeUpdateRateChangeDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_STATSUPDATERATE>,   SwitchScreenAction<StatsUpdateRateChangeDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_DISPLAYUPDATERATE>, SwitchScreenAction<DisplayUpdateRateChangeDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_DISPLAYREDRAWRATE>, SwitchScreenAction<DisplayRedrawRateChangeDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,              SwitchScreenAction<BoardcomputerHardwareSettingsMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
}

void TimersMenu::back()
{
    switchScreen<BoardcomputerHardwareSettingsMenu>();
}
