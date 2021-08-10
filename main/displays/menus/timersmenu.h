#pragma once

// local includes
#include "changevaluedisplay.h"
#include "menudisplay.h"
#include "utils.h"
#include "actions/switchscreenaction.h"
#include "icons/back.h"
#include "texts.h"
#include "accessors/settingsaccessors.h"

// forward declares
namespace {
class BoardcomputerHardwareSettingsMenu;
} // namespace

namespace {
class TimersMenu;

using PotiReadRateChangeDisplay = makeComponent<
    ChangeValueDisplay<int16_t>,
    StaticText<TEXT_POTIREADRATE>,
    PotiReadRateAccessor,
    BackActionInterface<SwitchScreenAction<TimersMenu>>,
    SwitchScreenAction<TimersMenu>
>;

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

#ifdef FEATURE_CAN
using CanReceiveRateChangeDisplay = makeComponent<
    ChangeValueDisplay<int16_t>,
    StaticText<TEXT_CANRECEIVERATE>,
    CanReceiveRateAccessor,
    BackActionInterface<SwitchScreenAction<TimersMenu>>,
    SwitchScreenAction<TimersMenu>
>;
#endif

#ifdef FEATURE_CLOUD
using CloudSendRateChangeDisplay = makeComponent<
    ChangeValueDisplay<int16_t>,
    StaticText<TEXT_CLOUDSENDRATE>,
    CloudSendRateAccessor,
    BackActionInterface<SwitchScreenAction<TimersMenu>>,
    SwitchScreenAction<TimersMenu>
>;
#endif

class TimersMenu :
    public MenuDisplay,
    public StaticText<TEXT_TIMERS>,
    public BackActionInterface<SwitchScreenAction<BoardcomputerHardwareSettingsMenu>>
{
public:
    TimersMenu()
    {
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_POTIREADRATE>,      SwitchScreenAction<PotiReadRateChangeDisplay>>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_MODEUPDATERATE>,    SwitchScreenAction<ModeUpdateRateChangeDisplay>>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_STATSUPDATERATE>,   SwitchScreenAction<StatsUpdateRateChangeDisplay>>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_DISPLAYUPDATERATE>, SwitchScreenAction<DisplayUpdateRateChangeDisplay>>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_DISPLAYREDRAWRATE>, SwitchScreenAction<DisplayRedrawRateChangeDisplay>>>();
#ifdef FEATURE_CAN
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_CANRECEIVERATE>,    SwitchScreenAction<CanReceiveRateChangeDisplay>>>();
#endif
#ifdef FEATURE_CLOUD
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_CLOUDSENDRATE>,     SwitchScreenAction<CloudSendRateChangeDisplay>>>();
#endif
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,              SwitchScreenAction<BoardcomputerHardwareSettingsMenu>, StaticMenuItemIcon<&icons::back>>>();
    }
};
} // namespace
