#include "ledstripanimationactions.h"
#ifdef FEATURE_LEDSTRIP
void LedStripSetAnimationAction::triggered()
{
    if (auto result = configs.write_config(configs.ledstrip.animationType, m_animation); !result)
        BobbyErrorHandler{}.errorOccured(std::move(result).error());
}
#endif
