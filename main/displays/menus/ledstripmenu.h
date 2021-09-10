#pragma once

// local includes
#include "menudisplay.h"
#include "menuitem.h"
#include "actions/toggleboolaction.h"
#include "actions/switchscreenaction.h"
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

struct BlinkAnimationAccessor : public RefAccessor<int16_t> { int16_t &getRef() const override { return blinkAnimation; } };

using BlinkAnimationChangeScreen = makeComponent<
    ChangeValueDisplay<int16_t>,
    StaticText<TEXT_BLINKANIMATION>,
    BlinkAnimationAccessor,
    BackActionInterface<SwitchScreenAction<LedstripMenu>>,
    SwitchScreenAction<LedstripMenu>
>;

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

class LedstripMenu :
    public MenuDisplay,
    public StaticText<TEXT_LEDSTRIP>,
    public BackActionInterface<SwitchScreenAction<MainMenu>>
{
public:
    LedstripMenu()
    {
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_LEDANIMATION>, ToggleBoolAction, CheckboxIcon, EnableLedAnimationAccessor>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BRAKELIGHTS>,  ToggleBoolAction, CheckboxIcon, EnableBrakeLightsAccessor>>();
        constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_BLINKANIMATION, LedsCountAccessor>,   SwitchScreenAction<BlinkAnimationChangeScreen>>>();
        constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_LEDSCOUNT, LedsCountAccessor>,        SwitchScreenAction<LedsCountChangeScreen>>>();
        constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_CENTEROFFSET, CenterOffsetAccessor>,  SwitchScreenAction<CenterOffsetChangeScreen>>>();
        constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_SMALLOFFSET, SmallOffsetAccessor>,    SwitchScreenAction<SmallOffsetChangeScreen>>>();
        constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_BIGOFFSET, BigOffsetAccessor>,        SwitchScreenAction<BigOffsetChangeScreen>>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,         SwitchScreenAction<MainMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
    }
};
#endif
} // namespace
