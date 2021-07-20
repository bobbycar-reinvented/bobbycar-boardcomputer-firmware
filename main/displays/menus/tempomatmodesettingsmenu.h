#pragma once

// local includes
#include "menudisplay.h"
#include "utils.h"
#include "changevaluedisplay.h"
#include "menuitem.h"
#include "actions/switchscreenaction.h"
#include "icons/back.h"
#include "texts.h"
#include "accessors/settingsaccessors.h"
#include "accessors/globalaccessors.h"
#include "actions/tempomatmodeapplycurrentpeedaction.h"

// forward declares
namespace {
class TempomatModeSettingsMenu;
class ModesSettingsMenu;
} // namespace

namespace {
using DefaultModeCruiseMotTgtChangeDisplay = makeComponent<
    ChangeValueDisplay<int16_t>,
    StaticText<TEXT_NCRUISEMOTTGT>,
    TempomatModeCruiseMotTgtAccessor,
    BackActionInterface<SwitchScreenAction<DefaultModeSettingsMenu>>,
    SwitchScreenAction<DefaultModeSettingsMenu>
>;

using TempomatModeModelModeChangeScreen = makeComponent<
    ChangeValueDisplay<UnifiedModelMode>,
    StaticText<TEXT_MODELMODE>,
    TempomatModeModelModeAccessor,
    BackActionInterface<SwitchScreenAction<TempomatModeSettingsMenu>>,
    SwitchScreenAction<TempomatModeSettingsMenu>
>;

class TempomatModeSettingsMenu :
    public MenuDisplay,
    public StaticText<TEXT_TEMPOMATMODESETTINGS>,
    public BackActionInterface<SwitchScreenAction<ModesSettingsMenu>>
{
public:
    TempomatModeSettingsMenu()
    {
        constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_APPLY, AvgSpeedAccessor>, TempomatModeApplyCurrentSpeedAction>>();
        constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_NCRUISEMOTTGT, TempomatModeCruiseMotTgtAccessor>, SwitchScreenAction<TempomatModeModelModeChangeScreen>>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_MODELMODE>, SwitchScreenAction<TempomatModeModelModeChangeScreen>>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,      SwitchScreenAction<ModesSettingsMenu>, StaticMenuItemIcon<&icons::back>>>();
    }
};
} // namespace
