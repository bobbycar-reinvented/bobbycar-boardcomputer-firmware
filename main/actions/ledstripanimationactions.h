#pragma once

// 3rdparty lib includes
#include "actioninterface.h"

// local includes
#include "ledstrip.h"
#include "ledstripdefines.h"
#include "newsettings.h"
#include "bobbyerrorhandler.h"

#ifdef FEATURE_LEDSTRIP
template<LedstripAnimation type>
class LedStripSetAnimationActionStatic : public virtual espgui::ActionInterface
{
public:
    void triggered() override
    {
        if (auto result = configs.write_config(configs.ledstrip.animationType, type); !result)
            BobbyErrorHandler{}.errorOccured(std::move(result).error());
    }
};

class LedStripSetAnimationAction : public virtual espgui::ActionInterface
{
public:
    LedStripSetAnimationAction(LedstripAnimation animation) : m_animation{animation} {};
    void triggered() override;
private:
    const LedstripAnimation m_animation;
};

#endif
