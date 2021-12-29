#include "ledstripselectblinkmenu.h"

#ifdef FEATURE_LEDSTRIP

// 3rdparty lib includes
#include "actions/dummyaction.h"
#include "actions/switchscreenaction.h"
#include "icons/back.h"

// local includes
#include "accessors/settingsaccessors.h"
#include "actions/ledstripblinkactions.h"
#include "displays/menus/ledstripmenu.h"
#include "bobbycheckbox.h"

using namespace espgui;

std::string currentSelectedBlinkAnimationText::text() const {
    switch (blinkAnimation) {
        case LEDSTRIP_OVERWRITE_BLINKLEFT:
#ifndef LEDSTRIP_WRONG_DIRECTION
            return TEXT_ANIMATION_BLINKLEFT;
#else
            return TEXT_ANIMATION_BLINKRIGHT;
#endif
        case LEDSTRIP_OVERWRITE_BLINKRIGHT:
#ifndef LEDSTRIP_WRONG_DIRECTION
            return TEXT_ANIMATION_BLINKRIGHT;
#else
            return TEXT_ANIMATION_BLINKLEFT;
#endif
        case LEDSTRIP_OVERWRITE_BLINKBOTH:
            return TEXT_ANIMATION_BLINKBOTH;
        default:
            return TEXT_ANIMATION_BLINKNONE;
    }
}

LedstripSelectBlinkMenu::LedstripSelectBlinkMenu()
{
    constructMenuItem<makeComponent<MenuItem, currentSelectedBlinkAnimationText,             DisabledColor, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, EmptyText,                                     DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ANIMATION_BLINKNONE>,          LedstripAnimationBlinkNoneAction>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ANIMATION_BLINKLEFT>,          LedstripAnimationBlinkLeftAction>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ANIMATION_BLINKRIGHT>,         LedstripAnimationBlinkRightAction>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ANIMATION_BLINKBOTH>,          LedstripAnimationBlinkBothAction>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_LEDSTRIP_EN_BLINK_ANIM>,       BobbyCheckbox, LedstripEnableBlinkAnimationAccessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,                         SwitchScreenAction<LedstripMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
}

void LedstripSelectBlinkMenu::back()
{
    switchScreen<LedstripMenu>();
}
#endif
