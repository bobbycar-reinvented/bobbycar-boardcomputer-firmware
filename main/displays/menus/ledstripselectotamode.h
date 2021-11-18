#pragma once

// Local includes
#include "menudisplay.h"
#include "utils.h"
#include "menuitem.h"
#include "ledstrip.h"
#include "icons/back.h"
#include "texts.h"
#include "actions/switchscreenaction.h"
#include "accessors/settingsaccessors.h"
#include "ledstripmenu.h"

#ifdef FEATURE_LEDSTRIP
using namespace espgui;

template <OtaAnimationModes mode>
class LedstripChangeOtaAnimModeAction : public virtual ActionInterface
{
public:
    void triggered() override
    {
        settings.ledstrip.otaMode = mode;
        saveSettings();
    }
};

namespace {
    class ledstripOtaAnimationChangeMenu :
            public MenuDisplay,
            public StaticText<TEXT_BLINKANIMATION>,
            public BackActionInterface<SwitchScreenAction<LedstripMenu>>
    {
    public:
        ledstripOtaAnimationChangeMenu()
        {
            constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_OTAANIM_NONE>,          LedstripChangeOtaAnimModeAction<OtaAnimationModes::None>>>();
            constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_OTAANIM_PROGRESS>,      LedstripChangeOtaAnimModeAction<OtaAnimationModes::GreenProgressBar>>>();
            constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_OTAANIM_COLOR>,         LedstripChangeOtaAnimModeAction<OtaAnimationModes::ColorChangeAll>>>();
            constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,                  SwitchScreenAction<LedstripMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
        }
    };
} // Namespace
#endif
