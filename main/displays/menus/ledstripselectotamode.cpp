#include "ledstripselectotamode.h"

#include "actions/switchscreenaction.h"
#include "icons/back.h"
#include "ledstripmenu.h"

// Local includes

#if defined(FEATURE_LEDSTRIP) && defined(FEATURE_OTA)
using namespace espgui;

ledstripOtaAnimationChangeMenu::ledstripOtaAnimationChangeMenu()
{
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_OTAANIM_NONE>,          LedstripChangeOtaAnimModeAction<OtaAnimationModes::None>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_OTAANIM_PROGRESS>,      LedstripChangeOtaAnimModeAction<OtaAnimationModes::GreenProgressBar>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_OTAANIM_COLOR>,         LedstripChangeOtaAnimModeAction<OtaAnimationModes::ColorChangeAll>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,                  SwitchScreenAction<LedstripMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
}

void ledstripOtaAnimationChangeMenu::back()
{
    switchScreen<LedstripMenu>();
}
#endif
