#pragma once

#include "menudisplay.h"
#include "staticmenudefinition.h"
#include "utils.h"
#include "changevaluedisplay.h"
#include "menuitem.h"
#include "actions/switchscreenaction.h"
#include "icons/back.h"
#include "texts.h"
#include "settingsaccessors.h"

namespace {
class LarsmModeSettingsMenu;
class ModesSettingsMenu;
}

namespace {
using LarsmModeModelModeChangeDisplay = makeComponent<
    ChangeValueDisplay<UnifiedModelMode>,
    StaticText<TEXT_SETMODELMODE>,
    LarsmModeModelModeAccessor,
    BackActionInterface<SwitchScreenAction<LarsmModeSettingsMenu>>,
    SwitchScreenAction<LarsmModeSettingsMenu>
>;
using LarsmModeModeChangeDisplay = makeComponent<
    ChangeValueDisplay<LarsmModeMode>,
    StaticText<TEXT_SETMODE>,
    LarsmModeModeAccessor,
    BackActionInterface<SwitchScreenAction<LarsmModeSettingsMenu>>,
    SwitchScreenAction<LarsmModeSettingsMenu>
>;
using LarsmModeIterationsChangeDisplay = makeComponent<
    ChangeValueDisplay<uint8_t>,
    StaticText<TEXT_SETITERATIONS>,
    LarsmModeIterationsAccessor,
    BackActionInterface<SwitchScreenAction<LarsmModeSettingsMenu>>,
    SwitchScreenAction<LarsmModeSettingsMenu>
>;

class LarsmModeSettingsMenu :
    public MenuDisplay,
    public StaticText<TEXT_LARSMMODESETTINGS>,
    public BackActionInterface<SwitchScreenAction<ModesSettingsMenu>>,
    public StaticMenuDefinition<
        makeComponent<MenuItem, StaticText<TEXT_SETMODELMODE>,  SwitchScreenAction<LarsmModeModelModeChangeDisplay>>,
        makeComponent<MenuItem, StaticText<TEXT_SETMODE>,       SwitchScreenAction<LarsmModeModeChangeDisplay>>,
        makeComponent<MenuItem, StaticText<TEXT_SETITERATIONS>, SwitchScreenAction<LarsmModeIterationsChangeDisplay>>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,          SwitchScreenAction<ModesSettingsMenu>, StaticMenuItemIcon<&icons::back>>
    >
{};
}
