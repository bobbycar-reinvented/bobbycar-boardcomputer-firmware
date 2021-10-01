#pragma once
// local includes
#include "menudisplay.h"
#include "menuitem.h"
#include "actions/toggleboolaction.h"
#include "actions/switchscreenaction.h"
#include "ledstripselectanimationmenu.h"
#include "ledstripselectblinkmenu.h"
#include "texts.h"
#include "icons/back.h"
#include "checkboxicon.h"
#include "globals.h"
#include "accessors/settingsaccessors.h"
#ifdef FEATURE_LEDSTRIP
#include "ledstrip.h"
#endif
#include "changevaluedisplay.h"

// forward declares
namespace {
class MainWindow;
} // namespace

using namespace espgui;

namespace {
#ifdef FEATURE_LEDSTRIP
class LedstripMenu;
class LedstripSelectAnimationMenu;

using LedsCountChangeScreen = makeComponent<
    ChangeValueDisplay<int16_t>,
    StaticText<TEXT_LEDSCOUNT>,
    LedsCountAccessor,
    BackActionInterface<SwitchScreenAction<LedstripMenu>>,
    SwitchScreenAction<LedstripMenu>
>;

using CenterOffsetChangeScreen = makeComponent<
    ChangeValueDisplay<int16_t>,
    StaticText<TEXT_CENTEROFFSET>,
    CenterOffsetAccessor,
    BackActionInterface<SwitchScreenAction<LedstripMenu>>,
    SwitchScreenAction<LedstripMenu>
>;

using SmallOffsetChangeScreen = makeComponent<
    ChangeValueDisplay<int16_t>,
    StaticText<TEXT_SMALLOFFSET>,
    SmallOffsetAccessor,
    BackActionInterface<SwitchScreenAction<LedstripMenu>>,
    SwitchScreenAction<LedstripMenu>
>;

using BigOffsetChangeScreen = makeComponent<
    ChangeValueDisplay<int16_t>,
    StaticText<TEXT_BIGOFFSET>,
    BigOffsetAccessor,
    BackActionInterface<SwitchScreenAction<LedstripMenu>>,
    SwitchScreenAction<LedstripMenu>
>;

using DeziampereChangeScreen = makeComponent<
    ChangeValueDisplay<int16_t>,
    StaticText<TEXT_LEDSTRIP_MILLIAMP>,
    DeziampereAccessor,
    BackActionInterface<SwitchScreenAction<LedstripMenu>>,
    SwitchScreenAction<LedstripMenu>
>;

class LedstripMenu :
    public MenuDisplay,
    public StaticText<TEXT_LEDSTRIP>,
    public BackActionInterface<SwitchScreenAction<MainMenu>>
{
public:
    LedstripMenu()
    {
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_LEDANIMATION>, ToggleBoolAction, CheckboxIcon,    EnableLedAnimationAccessor>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BRAKELIGHTS>,  ToggleBoolAction, CheckboxIcon,    EnableBrakeLightsAccessor>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BLINKBEEP>, ToggleBoolAction, CheckboxIcon,       EnableBeepWhenBlinkAccessor>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_FULLBLINK>, ToggleBoolAction, CheckboxIcon,       EnableFullBlinkAccessor>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_SELECTANIMATION>,                                 SwitchScreenAction<LedstripSelectAnimationMenu>>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BLINKANIMATION>,                                  SwitchScreenAction<LedstripSelectBlinkMenu>>>();
        constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_LEDSCOUNT, LedsCountAccessor>,           SwitchScreenAction<LedsCountChangeScreen>>>();
        constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_CENTEROFFSET, CenterOffsetAccessor>,     SwitchScreenAction<CenterOffsetChangeScreen>>>();
        constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_SMALLOFFSET, SmallOffsetAccessor>,       SwitchScreenAction<SmallOffsetChangeScreen>>>();
        constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_BIGOFFSET, BigOffsetAccessor>,           SwitchScreenAction<BigOffsetChangeScreen>>>();
        constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_LEDSTRIP_MILLIAMP, DeziampereAccessor>,  SwitchScreenAction<DeziampereChangeScreen>>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,                                            SwitchScreenAction<MainMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
    }
};
#endif
} // namespace
