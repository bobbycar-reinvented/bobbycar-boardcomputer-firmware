#pragma once

// Local includes
#include "menudisplay.h"
#include "utils.h"
#include "menuitem.h"
#include "ledstrip.h"
#include "ledstripselectanimationmenu.h"
#include "icons/back.h"
#include "texts.h"
#include "actions/dummyaction.h"
#include "actions/ledstripblinkactions.h"
#include "actions/switchscreenaction.h"
#include "ledstripdefines.h"

#ifdef FEATURE_LEDSTRIP
class currentSelectedBlinkAnimationText : public virtual TextInterface { public: std::string text() const override {
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
    };
};

using namespace espgui;

namespace {
    class LedstripSelectBlinkMenu :
            public MenuDisplay,
            public StaticText<TEXT_BLINKANIMATION>,
            public BackActionInterface<SwitchScreenAction<LedstripMenu>>
    {
    public:
        LedstripSelectBlinkMenu()
        {
            constructMenuItem<makeComponent<MenuItem, currentSelectedBlinkAnimationText,             DisabledColor, DummyAction>>();
            constructMenuItem<makeComponent<MenuItem, EmptyText,                                     DummyAction>>();
            constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ANIMATION_BLINKNONE>,          LedstripAnimationBlinkNoneAction>>();
            constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ANIMATION_BLINKLEFT>,          LedstripAnimationBlinkLeftAction>>();
            constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ANIMATION_BLINKRIGHT>,         LedstripAnimationBlinkRightAction>>();
            constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ANIMATION_BLINKBOTH>,          LedstripAnimationBlinkBothAction>>();
            constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,                         SwitchScreenAction<LedstripMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
        }
    };
} // Namespace
#endif
