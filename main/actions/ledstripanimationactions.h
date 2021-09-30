#pragma once

#include "actioninterface.h"
#include "utils.h"
#include "globals.h"
#include "ledstrip.h"
#include "ledstripdefines.h"

using namespace espgui;

namespace {
class LedstripAnimationDefaultRainbowAction : public virtual ActionInterface
{
public:
    void triggered() override { blinkAnimation = LEDSTRIP_ANIMATION_DEFAULT; }
};

class LedstripAnimationBlinkLeftAction : public virtual ActionInterface
{
public:
    void triggered() override { blinkAnimation = LEDSTRIP_ANIMATION_BLINKLEFT; }
};

class LedstripAnimationBlinkRightAction : public virtual ActionInterface
{
public:
    void triggered() override { blinkAnimation = LEDSTRIP_ANIMATION_BLINKRIGHT; }
};

class LedstripAnimationBlinkBothAction : public virtual ActionInterface
{
public:
    void triggered() override { blinkAnimation = LEDSTRIP_ANIMATION_BLINKBOTH; }
};
}
