#pragma once

#include <ratio>

// local includes
#include "menudisplay.h"
#include "utils.h"
#include "changevaluedisplay.h"
#include "actions/toggleboolaction.h"
#include "actions/switchscreenaction.h"
#include "checkboxicon.h"
#include "icons/back.h"
#include "texts.h"
#include "globals.h"
#include "accessors/settingsaccessors.h"

// forward declares
namespace {
class ControllerHardwareSettingsMenu;
class BoardcomputerHardwareSettingsMenu;
class EnableMenu;
class InvertMenu;
class SettingsMenu;
} // namespace

namespace {
using WheelDiameterMmChangeScreen = makeComponent<
    ChangeValueDisplay<int16_t>,
    StaticText<TEXT_WHEELDIAMETERMM>,
    WheelDiameterMmAccessor,
    BackActionInterface<SwitchScreenAction<ControllerHardwareSettingsMenu>>,
    SwitchScreenAction<ControllerHardwareSettingsMenu>
>;
using WheelDiameterInchChangeScreen = makeComponent<
    ChangeValueDisplay<float>,
    StaticText<TEXT_WHEELDIAMETERINCH>,
    WheelDiameterInchAccessor,
    RatioNumberStep<float, std::ratio<1,10>>,
    BackActionInterface<SwitchScreenAction<ControllerHardwareSettingsMenu>>,
    SwitchScreenAction<ControllerHardwareSettingsMenu>
>;
using NumMagnetPolesChangeScreen = makeComponent<
    ChangeValueDisplay<int16_t>,
    StaticText<TEXT_NUMMAGNETPOLES>,
    NumMagnetPolesAccessor,
    BackActionInterface<SwitchScreenAction<ControllerHardwareSettingsMenu>>,
    SwitchScreenAction<ControllerHardwareSettingsMenu>
>;
#ifdef FEATURE_CAN
using CanTransmitTimeoutChangeScreen = makeComponent<
    ChangeValueDisplay<int16_t>,
    StaticText<TEXT_CANTRANSMITTIMEOUT>,
    CanTransmitTimeoutAccessor,
    BackActionInterface<SwitchScreenAction<ControllerHardwareSettingsMenu>>,
    SwitchScreenAction<ControllerHardwareSettingsMenu>
>;
using CanReceiveTimeoutChangeScreen = makeComponent<
    ChangeValueDisplay<int16_t>,
    StaticText<TEXT_CANRECEIVETIMEOUT>,
    CanReceiveTimeoutAccessor,
    BackActionInterface<SwitchScreenAction<ControllerHardwareSettingsMenu>>,
    SwitchScreenAction<ControllerHardwareSettingsMenu>
>;
#endif

class ControllerHardwareSettingsMenu :
    public MenuDisplay,
    public StaticText<TEXT_CONTROLLERHARDWARESETTINGS>,
    public BackActionInterface<SwitchScreenAction<SettingsMenu>>
{
public:
    ControllerHardwareSettingsMenu()
    {
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_SETENABLED>,        SwitchScreenAction<EnableMenu>>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_SETINVERTED>,       SwitchScreenAction<InvertMenu>>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_WHEELDIAMETERMM>,   SwitchScreenAction<WheelDiameterMmChangeScreen>>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_WHEELDIAMETERINCH>, SwitchScreenAction<WheelDiameterInchChangeScreen>>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_NUMMAGNETPOLES>,    SwitchScreenAction<NumMagnetPolesChangeScreen>>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_SWAPFRONTBACK>,     ToggleBoolAction, CheckboxIcon, SwapFrontBackAccessor>>();
#ifdef FEATURE_CAN
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_FRONTSENDCAN>,       ToggleBoolAction, CheckboxIcon, SendFrontCanCmdAccessor>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACKSENDCAN>,        ToggleBoolAction, CheckboxIcon, SendBackCanCmdAccessor>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_CANTRANSMITTIMEOUT>, SwitchScreenAction<CanTransmitTimeoutChangeScreen>>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_CANRECEIVETIMEOUT>,  SwitchScreenAction<CanReceiveTimeoutChangeScreen>>>();
#endif
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,              SwitchScreenAction<SettingsMenu>, StaticMenuItemIcon<&icons::back>>>();
    }
};
} // namespace
