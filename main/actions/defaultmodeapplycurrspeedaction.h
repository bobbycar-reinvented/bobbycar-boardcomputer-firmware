#pragma once

// local includes
#include "actioninterface.h"
#include "globals.h"
#include "modes/defaultmode.h"

namespace {
class DefaultModeApplyCurrentSpeedAction : public virtual ActionInterface
{
public:
    void triggered() override
    {
        modes::defaultMode.nCruiseMotTgt = avgSpeed;
    }
};
} // namespace
