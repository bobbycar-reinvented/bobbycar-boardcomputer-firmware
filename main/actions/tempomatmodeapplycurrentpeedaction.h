#pragma once

// local includes
#include "actioninterface.h"
#include "globals.h"
#include "modes/tempomatmode.h"

using namespace espgui;

namespace {
class TempomatModeApplyCurrentSpeedAction : public virtual ActionInterface
{
public:
    void triggered() override
    {
        using namespace bobby;

        modes::tempomatMode.nCruiseMotTgt = avgSpeed;
    }
};
} // namespace
