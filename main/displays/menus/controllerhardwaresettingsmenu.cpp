#include "controllerhardwaresettingsmenu.h"

// system includes
#include <ratio>

// 3rdparty lib includes
#include "changevaluedisplay.h"
#include "actions/switchscreenaction.h"
#include "icons/back.h"

// local includes
#include "displays/bobbychangevaluedisplay.h"
#include "utils.h"
#include "globals.h"
#include "accessors/settingsaccessors.h"
#include "displays/menus/enablemenu.h"
#include "displays/menus/invertmenu.h"
#include "displays/menus/settingsmenu.h"
#include "bobbycheckbox.h"

namespace {
constexpr char TEXT_CONTROLLERHARDWARESETTINGS[] = "Controller H/W settings";
constexpr char TEXT_WHEELDIAMETERMM[] = "Wheel diameter (mm)";
constexpr char TEXT_WHEELDIAMETERINCH[] = "Wheel diameter (inch)";
constexpr char TEXT_NUMMAGNETPOLES[] = "Num magnet poles";
constexpr char TEXT_SETENABLED[] = "Set enabled";
constexpr char TEXT_SETINVERTED[] = "Set inverted";
constexpr char TEXT_SWAPFRONTBACK[] = "Swap front/back";
#ifdef FEATURE_CAN
constexpr char TEXT_FRONTSENDCAN[] = "Front send CAN";
constexpr char TEXT_BACKSENDCAN[] = "Back send CAN";
constexpr char TEXT_CANTRANSMITTIMEOUT[] = "CanTransmitTimeout";
constexpr char TEXT_CANRECEIVETIMEOUT[] = "CanReceiveTimeout";
constexpr char TEXT_CANRESETONERROR[] = "Reset on error";
#endif
constexpr char TEXT_BACK[] = "Back";

using WheelDiameterMmChangeScreen = espgui::makeComponent<
    BobbyChangeValueDisplay<int16_t>,
    espgui::StaticText<TEXT_WHEELDIAMETERMM>,
    WheelDiameterMmAccessor,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<ControllerHardwareSettingsMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<ControllerHardwareSettingsMenu>>
>;
using WheelDiameterInchChangeScreen = espgui::makeComponent<
    BobbyChangeValueDisplay<float>,
    espgui::StaticText<TEXT_WHEELDIAMETERINCH>,
    WheelDiameterInchAccessor,
    espgui::RatioNumberStep<float, std::ratio<1,10>>,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<ControllerHardwareSettingsMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<ControllerHardwareSettingsMenu>>
>;
using NumMagnetPolesChangeScreen = espgui::makeComponent<
    BobbyChangeValueDisplay<int16_t>,
    espgui::StaticText<TEXT_NUMMAGNETPOLES>,
    NumMagnetPolesAccessor,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<ControllerHardwareSettingsMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<ControllerHardwareSettingsMenu>>
>;
#ifdef FEATURE_CAN
using CanTransmitTimeoutChangeScreen = espgui::makeComponent<
    BobbyChangeValueDisplay<int16_t>,
    espgui::StaticText<TEXT_CANTRANSMITTIMEOUT>,
    CanTransmitTimeoutAccessor,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<ControllerHardwareSettingsMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<ControllerHardwareSettingsMenu>>
>;
using CanReceiveTimeoutChangeScreen = espgui::makeComponent<
    BobbyChangeValueDisplay<int16_t>,
    espgui::StaticText<TEXT_CANRECEIVETIMEOUT>,
    CanReceiveTimeoutAccessor,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<ControllerHardwareSettingsMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<ControllerHardwareSettingsMenu>>
>;
#endif
} // namespace

ControllerHardwareSettingsMenu::ControllerHardwareSettingsMenu()
{
    using namespace espgui;
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_SETENABLED>,         SwitchScreenAction<EnableMenu>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_SETINVERTED>,        SwitchScreenAction<InvertMenu>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_WHEELDIAMETERMM>,    SwitchScreenAction<WheelDiameterMmChangeScreen>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_WHEELDIAMETERINCH>,  SwitchScreenAction<WheelDiameterInchChangeScreen>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_NUMMAGNETPOLES>,     SwitchScreenAction<NumMagnetPolesChangeScreen>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_SWAPFRONTBACK>,      BobbyCheckbox, SwapFrontBackAccessor>>();
#ifdef FEATURE_CAN
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_FRONTSENDCAN>,       BobbyCheckbox, SendFrontCanCmdAccessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACKSENDCAN>,        BobbyCheckbox, SendBackCanCmdAccessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_CANTRANSMITTIMEOUT>, SwitchScreenAction<CanTransmitTimeoutChangeScreen>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_CANRECEIVETIMEOUT>,  SwitchScreenAction<CanReceiveTimeoutChangeScreen>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_CANRESETONERROR>,    BobbyCheckbox, CanResetOnErrorAccessor>>();
#endif
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,               SwitchScreenAction<SettingsMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
}

std::string ControllerHardwareSettingsMenu::text() const
{
    return TEXT_CONTROLLERHARDWARESETTINGS;
}

void ControllerHardwareSettingsMenu::back()
{
    espgui::switchScreen<SettingsMenu>();
}
