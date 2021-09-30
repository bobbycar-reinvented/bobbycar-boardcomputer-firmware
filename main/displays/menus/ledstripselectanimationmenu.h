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
#include "actions/ledstripanimationactions.h"
#include "actions/switchscreenaction.h"

using namespace espgui;

namespace  {
    class LedstripMenu;
}

namespace  {
    class LedstripSelectAnimationMenu :
            public MenuDisplay,
            public StaticText<TEXT_SELECTANIMATION>,
            public BackActionInterface<SwitchScreenAction<LedstripMenu>>
    {
    public:
        LedstripSelectAnimationMenu()
        {
            constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ANIMATION_DEFAULTRAINBOW>,     LedstripAnimationDefaultRainbowAction>>();
            constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ANIMATION_BLINKLEFT>,          LedstripAnimationBlinkLeftAction>>();
            constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ANIMATION_BLINKRIGHT>,         LedstripAnimationBlinkRightAction>>();
            constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ANIMATION_BLINKBOTH>,          LedstripAnimationBlinkBothAction>>();
            constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ANIMATION_BETTERRAINBOW>,      LedstripAnimationBetterRainbowAction>>();
            constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ANIMATION_SPEEDSYNCANIMATION>, LedstripAnimationSyncToSpeedAction>>();
            constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,                         SwitchScreenAction<LedstripMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
        }
    };
} // Namespace
