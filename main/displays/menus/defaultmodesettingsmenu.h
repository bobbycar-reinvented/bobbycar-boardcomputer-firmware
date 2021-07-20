#pragma once

// local includes
#include "menudisplay.h"
#include "utils.h"
#include "changevaluedisplay.h"
#include "menuitem.h"
#include "actions/toggleboolaction.h"
#include "actions/switchscreenaction.h"
#include "checkboxicon.h"
#include "icons/back.h"
#include "texts.h"
#include "accessors/settingsaccessors.h"

// forward declares
namespace {
class DefaultModeSettingsMenu;
class ModesSettingsMenu;
} // namespace

namespace {
using DefaultModeModelModeChangeDisplay = makeComponent<
    ChangeValueDisplay<UnifiedModelMode>,
    StaticText<TEXT_MODELMODE>,
    DefaultModeModelModeAccessor,
    BackActionInterface<SwitchScreenAction<DefaultModeSettingsMenu>>,
    SwitchScreenAction<DefaultModeSettingsMenu>
>;
using DefaultModeSmoothingChangeDisplay = makeComponent<
    ChangeValueDisplay<int16_t>,
    StaticText<TEXT_SMOOTHINGVAL>,
    DefaultModeSmoothingAccessor,
    BackActionInterface<SwitchScreenAction<DefaultModeSettingsMenu>>,
    SwitchScreenAction<DefaultModeSettingsMenu>
>;
using DefaultModeFrontPercentageChangeDisplay = makeComponent<
    ChangeValueDisplay<int16_t>,
    StaticText<TEXT_FRONTPERCENTAGE>,
    DefaultModeFrontPercentageAccessor,
    BackActionInterface<SwitchScreenAction<DefaultModeSettingsMenu>>,
    SwitchScreenAction<DefaultModeSettingsMenu>
>;
using DefaultModeBackPercentageChangeDisplay = makeComponent<
    ChangeValueDisplay<int16_t>,
    StaticText<TEXT_BACKPERCENTAGE>,
    DefaultModeBackPercentageAccessor,
    BackActionInterface<SwitchScreenAction<DefaultModeSettingsMenu>>,
    SwitchScreenAction<DefaultModeSettingsMenu>
>;
using DefaultModeAddSchwelleChangeDisplay = makeComponent<
    ChangeValueDisplay<int16_t>,
    StaticText<TEXT_ADDSCHWELLE>,
    DefaultModeAddSchwelleAccessor,
    BackActionInterface<SwitchScreenAction<DefaultModeSettingsMenu>>,
    SwitchScreenAction<DefaultModeSettingsMenu>
>;
using DefaultModeGas1WertChangeDisplay = makeComponent<
    ChangeValueDisplay<int16_t>,
    StaticText<TEXT_ADDGASVAL>,
    DefaultModeGas1WertAccessor,
    BackActionInterface<SwitchScreenAction<DefaultModeSettingsMenu>>,
    SwitchScreenAction<DefaultModeSettingsMenu>
>;
using DefaultModeGas2WertChangeDisplay = makeComponent<
    ChangeValueDisplay<int16_t>,
    StaticText<TEXT_SUBGASVAL>,
    DefaultModeGas2WertAccessor,
    BackActionInterface<SwitchScreenAction<DefaultModeSettingsMenu>>,
    SwitchScreenAction<DefaultModeSettingsMenu>
>;
using DefaultModeBrems1WertChangeDisplay = makeComponent<
    ChangeValueDisplay<int16_t>,
    StaticText<TEXT_ADDBRAKEVAL>,
    DefaultModeBrems1WertAccessor,
    BackActionInterface<SwitchScreenAction<DefaultModeSettingsMenu>>,
    SwitchScreenAction<DefaultModeSettingsMenu>
>;
using DefaultModeBrems2WertChangeDisplay = makeComponent<
    ChangeValueDisplay<int16_t>,
    StaticText<TEXT_SUBBRAKEVAL>,
    DefaultModeBrems2WertAccessor,
    BackActionInterface<SwitchScreenAction<DefaultModeSettingsMenu>>,
    SwitchScreenAction<DefaultModeSettingsMenu>
>;

class DefaultModeSettingsMenu :
    public MenuDisplay,
    public StaticText<TEXT_DEFAULTMODESETTIGNS>,
    public BackActionInterface<SwitchScreenAction<ModesSettingsMenu>>
{
public:
    DefaultModeSettingsMenu()
    {
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_MODELMODE>,          SwitchScreenAction<DefaultModeModelModeChangeDisplay>>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_SQUAREGAS>,          ToggleBoolAction, CheckboxIcon,  DefaultModeSquareGasAccessor>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_SQUAREBREMS>,        ToggleBoolAction, CheckboxIcon,  DefaultModeSquareBremsAccessor>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ENABLESMOOTHING>,    ToggleBoolAction, CheckboxIcon,  DefaultModeEnableSmoothingAccessor>>();
        constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_SMOOTHINGVAL, DefaultModeSmoothingAccessor>,                     SwitchScreenAction<DefaultModeSmoothingChangeDisplay>>>();
        constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_FRONTPERCENTAGE, DefaultModeFrontPercentageAccessor>, SwitchScreenAction<DefaultModeFrontPercentageChangeDisplay>>>();
        constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_BACKPERCENTAGE, DefaultModeBackPercentageAccessor>,   SwitchScreenAction<DefaultModeBackPercentageChangeDisplay>>>();
        constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_ADDSCHWELLE, DefaultModeAddSchwelleAccessor>,                    SwitchScreenAction<DefaultModeAddSchwelleChangeDisplay>>>();
        constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_SUBGASVAL, DefaultModeGas2WertAccessor>,                         SwitchScreenAction<DefaultModeGas2WertChangeDisplay>>>();
        constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_SUBBRAKEVAL, DefaultModeBrems2WertAccessor>,                     SwitchScreenAction<DefaultModeBrems2WertChangeDisplay>>>();
        constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_ADDGASVAL, DefaultModeGas1WertAccessor>,                         SwitchScreenAction<DefaultModeGas1WertChangeDisplay>>>();
        constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_ADDBRAKEVAL, DefaultModeBrems1WertAccessor>,                     SwitchScreenAction<DefaultModeBrems1WertChangeDisplay>>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,                                                                    SwitchScreenAction<ModesSettingsMenu>, StaticMenuItemIcon<&icons::back>>>();
    }
};
} // namespace
