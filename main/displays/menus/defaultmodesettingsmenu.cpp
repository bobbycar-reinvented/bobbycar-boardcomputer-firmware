#include "defaultmodesettingsmenu.h"

// 3rdparty lib includes
#include <changevaluedisplay.h>
#include <menuitem.h>
#include <actions/switchscreenaction.h>
#include <actions/dummyaction.h>
#include <icons/back.h>
#include <textwithvaluehelper.h>

// local includes
#include "displays/bobbychangevaluedisplay.h"
#include "utils.h"
#include "changevaluedisplay_unifiedmodelmode.h"
#include "accessors/settingsaccessors.h"
#include "displays/menus/handbremssettingsmenu.h"
#include "displays/menus/modessettingsmenu.h"
#include "bobbycheckbox.h"

namespace {
using DefaultModeModelModeChangeDisplay = espgui::makeComponent<
    BobbyChangeValueDisplay<UnifiedModelMode>,
    espgui::StaticText<TEXT_MODELMODE>,
    DefaultModeModelModeAccessor,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<DefaultModeSettingsMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<DefaultModeSettingsMenu>>
>;
using DefaultModeHybridModelModeChangeDisplay = espgui::makeComponent<
    BobbyChangeValueDisplay<UnifiedModelMode>,
    espgui::StaticText<TEXT_HYBRIDMODE>,
    DefaultModeHybridModelModeAccessor,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<DefaultModeSettingsMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<DefaultModeSettingsMenu>>
>;
using DefaultModeSmoothingChangeDisplay = espgui::makeComponent<
    BobbyChangeValueDisplay<int16_t>,
    espgui::StaticText<TEXT_SMOOTHINGVAL>,
    DefaultModeSmoothingAccessor,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<DefaultModeSettingsMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<DefaultModeSettingsMenu>>
>;
using DefaultModeFwSmoothingLowerLimitChangeDisplay = espgui::makeComponent<
    BobbyChangeValueDisplay<int16_t>,
    espgui::StaticText<TEXT_FWSMOOTHING_LIMIT>,
    DefaultModeEnableFieldWeakSmoothingLowerLimitAccessor,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<DefaultModeSettingsMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<DefaultModeSettingsMenu>>
>;
using DefaultModeFrontPercentageChangeDisplay = espgui::makeComponent<
    BobbyChangeValueDisplay<int16_t>,
    espgui::StaticText<TEXT_FRONTPERCENTAGE>,
    DefaultModeFrontPercentageAccessor,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<DefaultModeSettingsMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<DefaultModeSettingsMenu>>
>;
using DefaultModeBackPercentageChangeDisplay = espgui::makeComponent<
    BobbyChangeValueDisplay<int16_t>,
    espgui::StaticText<TEXT_BACKPERCENTAGE>,
    DefaultModeBackPercentageAccessor,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<DefaultModeSettingsMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<DefaultModeSettingsMenu>>
>;
using DefaultModeAddSchwelleChangeDisplay = espgui::makeComponent<
    BobbyChangeValueDisplay<int16_t>,
    espgui::StaticText<TEXT_ADDSCHWELLE>,
    DefaultModeAddSchwelleAccessor,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<DefaultModeSettingsMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<DefaultModeSettingsMenu>>
>;
using DefaultModeGas1WertChangeDisplay = espgui::makeComponent<
    BobbyChangeValueDisplay<int16_t>,
    espgui::StaticText<TEXT_ADDGASVAL>,
    DefaultModeGas1WertAccessor,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<DefaultModeSettingsMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<DefaultModeSettingsMenu>>
>;
using DefaultModeGas2WertChangeDisplay = espgui::makeComponent<
    BobbyChangeValueDisplay<int16_t>,
    espgui::StaticText<TEXT_SUBGASVAL>,
    DefaultModeGas2WertAccessor,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<DefaultModeSettingsMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<DefaultModeSettingsMenu>>
>;
using DefaultModeBrems1WertChangeDisplay = espgui::makeComponent<
    BobbyChangeValueDisplay<int16_t>,
    espgui::StaticText<TEXT_ADDBRAKEVAL>,
    DefaultModeBrems1WertAccessor,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<DefaultModeSettingsMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<DefaultModeSettingsMenu>>
>;
using DefaultModeBrems2WertChangeDisplay = espgui::makeComponent<
    BobbyChangeValueDisplay<int16_t>,
    espgui::StaticText<TEXT_SUBBRAKEVAL>,
    DefaultModeBrems2WertAccessor,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<DefaultModeSettingsMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<DefaultModeSettingsMenu>>
>;
using DefaultModeHybridActivationLimitChangeDisplay = espgui::makeComponent<
    BobbyChangeValueDisplay<int16_t>,
    espgui::StaticText<TEXT_HYBRIDACTIVATIONLIMIT>,
    DefaultModeHybridActivationLimitAccessor,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<DefaultModeSettingsMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<DefaultModeSettingsMenu>>
>;
using DefaultModeHybridDeactivationLimitChangeDisplay = espgui::makeComponent<
    BobbyChangeValueDisplay<int16_t>,
    espgui::StaticText<TEXT_HYBRIDDEACTIVATIONLIMIT>,
    DefaultModeHybridDeactivationLimitAccessor,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<DefaultModeSettingsMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<DefaultModeSettingsMenu>>
>;
} // namespace

using namespace espgui;

DefaultModeSettingsMenu::DefaultModeSettingsMenu()
{
    auto diff = std::abs(settings.hybrid.activationLimit - settings.hybrid.deactivationLimit);
    if (diff < 20) { constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_LIMITS_TO_NEAR>, StaticFont<2>, StaticColor<TFT_RED>, DummyAction>>(); }
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_MODELMODE>,          SwitchScreenAction<DefaultModeModelModeChangeDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_HYBRIDMODE>,         SwitchScreenAction<DefaultModeHybridModelModeChangeDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_SQUAREGAS>,          BobbyCheckbox,  DefaultModeSquareGasAccessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_SQUAREBREMS>,        BobbyCheckbox,  DefaultModeSquareBremsAccessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ENABLESMOOTHINGUP>,    BobbyCheckbox,  DefaultModeEnableSmoothingUpAccessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ENABLESMOOTHINGDOWN>,    BobbyCheckbox,  DefaultModeEnableSmoothingDownAccessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ENABLEFWSMOOTHINGUP>,  BobbyCheckbox,  DefaultModeEnableFieldWeakSmoothingUpAccessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ENABLEFWSMOOTHINGDOWN>,  BobbyCheckbox,  DefaultModeEnableFieldWeakSmoothingDownAccessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_HYBRIDENABLE>,          BobbyCheckbox,  DefaultModeEnableHybridAccessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_HANDBREMSE>,            SwitchScreenAction<HandbremsSettingsMenu>>>();
    constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_FWSMOOTHING_LIMIT, DefaultModeEnableFieldWeakSmoothingLowerLimitAccessor>, SwitchScreenAction<DefaultModeFwSmoothingLowerLimitChangeDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_SMOOTHINGVAL, DefaultModeSmoothingAccessor>,                     SwitchScreenAction<DefaultModeSmoothingChangeDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_FRONTPERCENTAGE, DefaultModeFrontPercentageAccessor>, SwitchScreenAction<DefaultModeFrontPercentageChangeDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_BACKPERCENTAGE, DefaultModeBackPercentageAccessor>,   SwitchScreenAction<DefaultModeBackPercentageChangeDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_ADDSCHWELLE, DefaultModeAddSchwelleAccessor>,                    SwitchScreenAction<DefaultModeAddSchwelleChangeDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_SUBGASVAL, DefaultModeGas2WertAccessor>,                         SwitchScreenAction<DefaultModeGas2WertChangeDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_SUBBRAKEVAL, DefaultModeBrems2WertAccessor>,                     SwitchScreenAction<DefaultModeBrems2WertChangeDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_ADDGASVAL, DefaultModeGas1WertAccessor>,                         SwitchScreenAction<DefaultModeGas1WertChangeDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_ADDBRAKEVAL, DefaultModeBrems1WertAccessor>,                     SwitchScreenAction<DefaultModeBrems1WertChangeDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_HYBRIDACTIVATIONLIMIT, DefaultModeHybridActivationLimitAccessor>,        SwitchScreenAction<DefaultModeHybridActivationLimitChangeDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_HYBRIDDEACTIVATIONLIMIT, DefaultModeHybridDeactivationLimitAccessor>,    SwitchScreenAction<DefaultModeHybridDeactivationLimitChangeDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,                                                                    SwitchScreenAction<ModesSettingsMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
}

void DefaultModeSettingsMenu::back()
{
    switchScreen<ModesSettingsMenu>();
}
