#pragma once

// local includes
#include "menudisplay.h"
#include "utils.h"
#include "changevaluedisplay.h"
#include "menuitem.h"
#include "actions/switchscreenaction.h"
#include "icons/back.h"
#include "texts.h"
#include "settingsaccessors.h"

// forward declares
namespace {
class LimitsSettingsMenu;
class SettingsMenu;
} // namespace

namespace {
using IMotMaxChangeScreen = makeComponent<
    ChangeValueDisplay<int16_t>,
    StaticText<TEXT_SETIMOTMAX>,
    IMotMaxAccessor,
    BackActionInterface<SwitchScreenAction<LimitsSettingsMenu>>,
    SwitchScreenAction<LimitsSettingsMenu>
>;
using IDcMaxChangeScreen = makeComponent<
    ChangeValueDisplay<int16_t>,
    StaticText<TEXT_SETIDCMAX>,
    IDcMaxAccessor,
    BackActionInterface<SwitchScreenAction<LimitsSettingsMenu>>,
    SwitchScreenAction<LimitsSettingsMenu>
>;
using NMotMaxKmhChangeScreen = makeComponent<
    ChangeValueDisplay<int16_t>,
    StaticText<TEXT_SETNMOTMAXKMH>,
    NMotMaxKmhAccessor,
    BackActionInterface<SwitchScreenAction<LimitsSettingsMenu>>,
    SwitchScreenAction<LimitsSettingsMenu>
>;
using NMotMaxRpmChangeScreen = makeComponent<
    ChangeValueDisplay<int16_t>,
    StaticText<TEXT_SETNMOTMAX>,
    NMotMaxRpmAccessor,
    BackActionInterface<SwitchScreenAction<LimitsSettingsMenu>>,
    SwitchScreenAction<LimitsSettingsMenu>
>;
using FieldWeakMaxChangeScreen = makeComponent<
    ChangeValueDisplay<int16_t>,
    StaticText<TEXT_SETFIELDWEAKMAX>,
    FieldWeakMaxAccessor,
    BackActionInterface<SwitchScreenAction<LimitsSettingsMenu>>,
    SwitchScreenAction<LimitsSettingsMenu>
>;
using PhaseAdvMaxChangeScreen = makeComponent<
    ChangeValueDisplay<int16_t>,
    StaticText<TEXT_SETPHASEADVMAX>,
    PhaseAdvMaxAccessor,
    BackActionInterface<SwitchScreenAction<LimitsSettingsMenu>>,
    SwitchScreenAction<LimitsSettingsMenu>
>;

class LimitsSettingsMenu :
    public MenuDisplay,
    public StaticText<TEXT_LIMITSSETTINGS>,
    public BackActionInterface<SwitchScreenAction<SettingsMenu>>
{
public:
    LimitsSettingsMenu()
    {
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_SETIMOTMAX>,      SwitchScreenAction<IMotMaxChangeScreen>>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_SETIDCMAX>,       SwitchScreenAction<IDcMaxChangeScreen>>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_SETNMOTMAXKMH>,   SwitchScreenAction<NMotMaxKmhChangeScreen>>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_SETNMOTMAX>,      SwitchScreenAction<NMotMaxRpmChangeScreen>>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_SETFIELDWEAKMAX>, SwitchScreenAction<FieldWeakMaxChangeScreen>>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_SETPHASEADVMAX>,  SwitchScreenAction<PhaseAdvMaxChangeScreen>>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,            SwitchScreenAction<SettingsMenu>, StaticMenuItemIcon<&icons::back>>>();
    }
};
} // namespace
