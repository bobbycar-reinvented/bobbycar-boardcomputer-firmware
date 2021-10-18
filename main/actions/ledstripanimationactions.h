#pragma once

#include "actioninterface.h"
#include "utils.h"
#include "globals.h"
#include "ledstrip.h"
// #include "ledstripdefines.h"

using namespace espgui;

namespace {
template<int16_t type>
class LedStripSetAnimationAction : public virtual ActionInterface
{
public:
    void triggered() override { animation_type = type; }
};

/*
class LedstripAnimationDefaultRainbowAction : public virtual ActionInterface
{
public:
    void triggered() override { animation_type = LEDSTRIP_ANIMATION_TYPE_DEFAULTRAINBOW; }
};

class LedstripAnimationBetterRainbowAction : public virtual ActionInterface
{
public:
    void triggered() override { animation_type = LEDSTRIP_ANIMATION_TYPE_BETTERRAINBOW; }
};

class LedstripAnimationSyncToSpeedAction : public virtual ActionInterface
{
public:
    void triggered() override { animation_type = LEDSTRIP_ANIMATION_TYPE_SPEEDSYNCANIMATION; }
};
*/
}
