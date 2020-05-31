#pragma once

#include "modeinterface.h"
#include "globals.h"
#include "utils.h"
#include "defaultmode.h"

#include "bobbycar-protocol/protocol.h"

namespace {
#ifdef FEATURE_GAMETRAK
class GametrakMode : public ModeInterface
{
public:
    void update() override;

    const char *displayName() const override { return "Gametrak"; }
};

namespace modes {
GametrakMode gametrakMode;
}

void GametrakMode::update()
{
    if (gas > 500. || brems > 500.)
    {
        modes::defaultMode.waitForGasLoslass = true;
        modes::defaultMode.waitForBremsLoslass = true;
        currentMode = &modes::defaultMode;
        return;
    }

    for (MotorState &motor : motors())
    {
        motor.ctrlTyp = ControlType::FieldOrientedControl;
        motor.ctrlMod = ControlMode::Speed;
        motor.pwm = gametrakDist > 200 ? 20 : 0;
    }

    fixCommonParams();

    sendCommands();
}
#endif
}
