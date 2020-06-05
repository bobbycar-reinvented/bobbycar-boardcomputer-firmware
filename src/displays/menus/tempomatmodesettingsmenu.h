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
class TempomatModeSettingsMenu;
class ModesSettingsMenu;
}

namespace {
using TempomatModeModelModeChangeScreen = makeComponent<
    ChangeValueDisplay<UnifiedModelMode>,
    StaticText<TEXT_SETMODELMODE>,
    TempomatModeModelModeAccessor,
    BackActionInterface<SwitchScreenAction<TempomatModeSettingsMenu>>,
    SwitchScreenAction<TempomatModeSettingsMenu>
>;

class TempomatModeSettingsMenu :
    public MenuDisplay,
    public StaticText<TEXT_TEMPOMATMODESETTINGS>,
    public BackActionInterface<SwitchScreenAction<ModesSettingsMenu>>,
    public StaticMenuDefinition<
        makeComponent<MenuItem, StaticText<TEXT_SETMODELMODE>, SwitchScreenAction<TempomatModeModelModeChangeScreen>>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,         SwitchScreenAction<ModesSettingsMenu>, StaticMenuItemIcon<&icons::back>>
    >
{};
}
