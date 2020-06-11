#pragma once

#include "changevaluedisplay.h"
#include "menudisplay.h"
#include "staticmenudefinition.h"
#include "utils.h"
#include "actions/switchscreenaction.h"
#include "icons/back.h"
#include "texts.h"
#include "settingsaccessors.h"

namespace {
class BoardcomputerHardwareSettingsMenu;
class TimersMenu :
    public MenuDisplay,
    public StaticText<TEXT_TIMERS>,
    public BackActionInterface<SwitchScreenAction<BoardcomputerHardwareSettingsMenu>>,
    public StaticMenuDefinition<
        // TODO
        makeComponent<MenuItem, StaticText<TEXT_BACK>,                    SwitchScreenAction<BoardcomputerHardwareSettingsMenu>, StaticMenuItemIcon<&icons::back>>
    >
{};
}
