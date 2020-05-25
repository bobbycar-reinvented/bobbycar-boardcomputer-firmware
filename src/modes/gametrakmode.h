#pragma once

#include "modeinterface.h"
#include "globals.h"
#include "utils.h"

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
    for (MotorState &motor : motors())
    {
        motor.ctrlTyp = ControlType::FieldOrientedControl;
        motor.ctrlMod = ControlMode::Speed;
        motor.pwm = 0;
    }

    fixCommonParams();

    sendCommands();
}
#endif
}
