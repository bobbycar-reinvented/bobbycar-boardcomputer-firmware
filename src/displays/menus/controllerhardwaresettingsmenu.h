#pragma once

#include <ratio>

// local includes
#include "menudisplay.h"
#include "containermenudefinition.h"
#include "utils.h"
#include "changevaluedisplay.h"
#include "actions/toggleboolaction.h"
#include "actions/switchscreenaction.h"
#include "checkboxicon.h"
#include "icons/back.h"
#include "texts.h"
#include "globals.h"
#include "settingsaccessors.h"

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

class ControllerHardwareSettingsMenu :
    public MenuDisplay,
    public StaticText<TEXT_CONTROLLERHARDWARESETTINGS>,
    public BackActionInterface<SwitchScreenAction<SettingsMenu>>,
    public ContainerMenuDefinition
{
public:
    ControllerHardwareSettingsMenu()
    {
        constructItem<makeComponent<MenuItem, StaticText<TEXT_SETENABLED>,        SwitchScreenAction<EnableMenu>>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_SETINVERTED>,       SwitchScreenAction<InvertMenu>>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_WHEELDIAMETERMM>,   SwitchScreenAction<WheelDiameterMmChangeScreen>>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_WHEELDIAMETERINCH>, SwitchScreenAction<WheelDiameterInchChangeScreen>>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_NUMMAGNETPOLES>,    SwitchScreenAction<NumMagnetPolesChangeScreen>>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_SWAPFRONTBACK>,     ToggleBoolAction, CheckboxIcon, SwapFrontBackAccessor>>();
        constructItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,              SwitchScreenAction<SettingsMenu>, StaticMenuItemIcon<&icons::back>>>();
    }
};
} // namespace
