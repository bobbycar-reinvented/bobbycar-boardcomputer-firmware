#include "ledstripmenu.h"

#ifdef FEATURE_LEDSTRIP
// 3rdparty lib includes
#include <FastLED.h>
#include <actioninterface.h>
#include <actions/switchscreenaction.h>
#include <changevaluedisplay.h>
#include <icons/back.h>
#include <menuitem.h>
#include <textwithvaluehelper.h>

// local includes
#include "displays/bobbychangevaluedisplay.h"
#include "accessors/settingsaccessors.h"
#include "displays/ledstripcolorsdisplay.h"
#include "displays/menus/ledstripselectotamode.h"
#include "displays/menus/mainmenu.h"
#include "globals.h"
#include "ledstrip.h"
#include "ledstripselectanimationmenu.h"
#include "ledstripselectblinkmenu.h"
#include "bobbycheckbox.h"

// clang-format off

namespace {
using LedsCountChangeScreen = espgui::makeComponent<
    BobbyChangeValueDisplay<int16_t>,
    espgui::StaticText<TEXT_LEDSCOUNT>,
    LedsCountAccessor,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<LedstripMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<LedstripMenu>>
>;

using CenterOffsetChangeScreen = espgui::makeComponent<
    BobbyChangeValueDisplay<int16_t>,
    espgui::StaticText<TEXT_CENTEROFFSET>,
    CenterOffsetAccessor,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<LedstripMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<LedstripMenu>>
>;

using SmallOffsetChangeScreen = espgui::makeComponent<
    BobbyChangeValueDisplay<int16_t>,
    espgui::StaticText<TEXT_SMALLOFFSET>,
    SmallOffsetAccessor,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<LedstripMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<LedstripMenu>>
>;

using BigOffsetChangeScreen = espgui::makeComponent<
    BobbyChangeValueDisplay<int16_t>,
    espgui::StaticText<TEXT_BIGOFFSET>,
    BigOffsetAccessor,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<LedstripMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<LedstripMenu>>
>;

using DeziampereChangeScreen = espgui::makeComponent<
    BobbyChangeValueDisplay<int16_t>,
    espgui::StaticText<TEXT_LEDSTRIP_MILLIAMP>,
    DeziampereAccessor,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<LedstripMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<LedstripMenu>>
>;

using StVOOffsetChangeScreen = espgui::makeComponent<
    BobbyChangeValueDisplay<int16_t>,
    espgui::StaticText<TEXT_STVO_FRONTOFFSET>,
    LedsStVOFrontOffsetAccessor,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<LedstripMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<LedstripMenu>>
>;

using StVOLengthChangeScreen = espgui::makeComponent<
    BobbyChangeValueDisplay<int16_t>,
    espgui::StaticText<TEXT_STVO_FRONTLENGTH>,
    LedsStVOFrontLengthAccessor,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<LedstripMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<LedstripMenu>>
>;

using animationMultiplierChangeScreen = espgui::makeComponent<
    BobbyChangeValueDisplay<int16_t>,
    espgui::StaticText<TEXT_ANIMATION_MULTIPLIER>,
    AnimationMultiplierAccessor,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<LedstripMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<LedstripMenu>>
>;

using ledstripBrightnessChangeScreen = espgui::makeComponent<
    BobbyChangeValueDisplay<uint8_t>,
    espgui::StaticText<TEXT_LEDSTRIP_BRIGHTNESS>,
    LedstripBrightnessAccessor,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<LedstripMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<LedstripMenu>>
>;

class AllCustomLedsOffAction : public virtual espgui::ActionInterface
{
public:
    void triggered() override
    {
        for(int index = 0; index < 8; index++)
        {
            ledstrip_custom_colors[index] = CRGB{0,0,0};
        }
    }
};
} // namespace

LedstripMenu::LedstripMenu()
{
    using namespace espgui;
    constructMenuItem<makeComponent<MenuItem, espgui::StaticText<TEXT_LEDSTRIPCOLORMENU>,                               espgui::SwitchScreenAction<LedstripColorsDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, espgui::StaticText<TEXT_LEDANIMATION>, BobbyCheckbox,    EnableLedAnimationAccessor>>();
    constructMenuItem<makeComponent<MenuItem, espgui::StaticText<TEXT_BRAKELIGHTS>,  BobbyCheckbox,    EnableBrakeLightsAccessor>>();
    constructMenuItem<makeComponent<MenuItem, espgui::StaticText<TEXT_BLINKBEEP>, BobbyCheckbox,       EnableBeepWhenBlinkAccessor>>();
    constructMenuItem<makeComponent<MenuItem, espgui::StaticText<TEXT_FULLBLINK>, BobbyCheckbox,       EnableFullBlinkAccessor>>();

    if (!simplified) { constructMenuItem<makeComponent<MenuItem, espgui::StaticText<TEXT_LEDSTRIP_STVO>, BobbyCheckbox,   EnableLedstripStVOAccessor>>(); }
    constructMenuItem<makeComponent<MenuItem, espgui::StaticText<TEXT_STVO_ENABLEFRONTLIGHT>, BobbyCheckbox,   EnableLedstripStVOFrontlight>>();
    constructMenuItem<makeComponent<MenuItem, espgui::StaticText<TEXT_LEDSTRIP_ALLCUSTOMOFF>, AllCustomLedsOffAction>>();
    if (!simplified) { constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_STVO_FRONTOFFSET, LedsStVOFrontOffsetAccessor>,    espgui::SwitchScreenAction<StVOOffsetChangeScreen>>>(); }
    if (!simplified) { constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_STVO_FRONTLENGTH, LedsStVOFrontLengthAccessor>,    espgui::SwitchScreenAction<StVOLengthChangeScreen>>>(); }

    constructMenuItem<makeComponent<MenuItem, espgui::StaticText<TEXT_SELECTANIMATION>,                                 espgui::SwitchScreenAction<LedstripSelectAnimationMenu>>>();
    constructMenuItem<makeComponent<MenuItem, espgui::StaticText<TEXT_BLINKANIMATION>,                                  espgui::SwitchScreenAction<LedstripSelectBlinkMenu>>>();
#ifdef FEATURE_OTA
    if (!simplified) { constructMenuItem<makeComponent<MenuItem, espgui::StaticText<TEXT_LEDSTRIP_CHANGE_OTA_ANIM>,     espgui::SwitchScreenAction<ledstripOtaAnimationChangeMenu>>>(); }
#endif
    constructMenuItem<makeComponent<MenuItem, espgui::StaticText<TEXT_ANIMATION_MULTIPLIER>,                            espgui::SwitchScreenAction<animationMultiplierChangeScreen>>>();
    if (!simplified) { constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_LEDSCOUNT, LedsCountAccessor>,           espgui::SwitchScreenAction<LedsCountChangeScreen>>>(); }
    if (!simplified) { constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_CENTEROFFSET, CenterOffsetAccessor>,     espgui::SwitchScreenAction<CenterOffsetChangeScreen>>>(); }
    if (!simplified) { constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_SMALLOFFSET, SmallOffsetAccessor>,       espgui::SwitchScreenAction<SmallOffsetChangeScreen>>>(); }
    if (!simplified) { constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_BIGOFFSET, BigOffsetAccessor>,           espgui::SwitchScreenAction<BigOffsetChangeScreen>>>(); }
    if (!simplified) { constructMenuItem<makeComponent<MenuItem, espgui::StaticText<TEXT_LEDSTRIP_BRIGHTNESS>,                             espgui::SwitchScreenAction<ledstripBrightnessChangeScreen>>>(); }
    if (!simplified) { constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_LEDSTRIP_MILLIAMP, DeziampereAccessor>,  espgui::SwitchScreenAction<DeziampereChangeScreen>>>(); }
    constructMenuItem<makeComponent<MenuItem, espgui::StaticText<TEXT_BACK>,                                            espgui::SwitchScreenAction<MainMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
}

void LedstripMenu::back()
{
    espgui::switchScreen<MainMenu>();
}
#endif
