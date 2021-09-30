#pragma once

#include "actioninterface.h"
#include "utils.h"
#include "globals.h"
#include "ledstrip.h"
#include "ledstripdefines.h"

using namespace espgui;

namespace {
class LedstripAnimationBlinkNoneAction : public virtual ActionInterface
{
public:
    void triggered() override { blinkAnimation = LEDSTRIP_OVERWRITE_NONE; }
};

class LedstripAnimationBlinkLeftAction : public virtual ActionInterface
{
public:
    void triggered() override { blinkAnimation = LEDSTRIP_OVERWRITE_BLINKLEFT; }
};

class LedstripAnimationBlinkRightAction : public virtual ActionInterface
{
public:
    void triggered() override { blinkAnimation = LEDSTRIP_OVERWRITE_BLINKRIGHT; }
};

class LedstripAnimationBlinkBothAction : public virtual ActionInterface
{
public:
    void triggered() override { blinkAnimation = LEDSTRIP_OVERWRITE_BLINKBOTH; }
};
}
