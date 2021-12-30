#pragma once

// 3rdparty lib includes
#include "actioninterface.h"

// local includes
#include "ledstrip.h"
#include "ledstripdefines.h"

#ifdef FEATURE_LEDSTRIP
template<LedstripAnimation type>
class LedStripSetAnimationAction : public virtual espgui::ActionInterface
{
public:
    void triggered() override { animation_type = type; }
};
#endif
