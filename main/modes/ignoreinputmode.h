#pragma once

// local includes
#include "bobbycar-common.h"
#include "modeinterface.h"

namespace bobby {

class IgnoreInputMode : public ModeInterface
{
public:
    IgnoreInputMode(int16_t pwm, bobbycar::protocol::ControlType ctrlTyp, bobbycar::protocol::ControlMode ctrlMod) :
        m_pwm{pwm}, m_ctrlTyp{ctrlTyp}, m_ctrlMod{ctrlMod}
    {
    }

    void update() override;

    const char *displayName() const override { return "IgnoreInput"; }

private:
    const int16_t m_pwm;
    const bobbycar::protocol::ControlType m_ctrlTyp;
    const bobbycar::protocol::ControlMode m_ctrlMod;
};

} // namespace bobby
