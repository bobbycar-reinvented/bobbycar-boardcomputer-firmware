#include <cmath>

#include "espchrono.h"
#include "mickmode.h"

// local includes
#include "globals.h"
#include "utils.h"

namespace modes {
MickMode mickMode;
} // namespace modes

void MickMode::start()
{
    Base::start();

    pwm_ = 0.f;
}

void MickMode::update()
{
    if (!gas || !brems)
    {
        start();

        for (bobbycar::protocol::serial::MotorState &motor : motors())
        {
            motor.ctrlTyp = bobbycar::protocol::ControlType::FieldOrientedControl;
            motor.ctrlMod = bobbycar::protocol::ControlMode::OpenMode;
            motor.pwm = 0;
            motor.cruiseCtrlEna = false;
            motor.nCruiseMotTgt = 0;
        }
    }
    else
    {
        auto now = espchrono::millis_clock::now();
        float timeDelta = std::chrono::floor<std::chrono::milliseconds>(now - lastUpdate_).count();
        // Make sure timeDelta can never be negative, otherwise the exponential below may explode
        timeDelta = std::max(timeDelta, 0.f);
        lastUpdate_ = now;

        float alpha = 1.f - expf(-timeDelta / profileSettings.mickMode.smoothing);
        // Fall back to fixed smoothing if this calculation fails
        if (!isfinite(alpha) || alpha < 0.f || alpha > 1.f)
            alpha = 0.02f;
        // Limit time constant to below 3 s at update rate of 20 ms to make stopping possible
        // if misconfiguration or corruption happens
        else if (alpha < 0.0066f)
            alpha = 0.0066f;

        float gasOf1500 = *gas * 1500.f / 1000.f;
        float brakeOf1500 = *brems * 1500.f / 1000.f;
        float controlInput = gasOf1500 - brakeOf1500;
        if (!isfinite(controlInput) || controlInput > 1500.f || controlInput < -1500.f)
            controlInput = 0.f;

        pwm_ = pwm_ * (1.f-alpha) + controlInput * alpha;
        // Should be in this range anyway, but clamp to make sure
        pwm_ = std::clamp(pwm_, -1500.f, 1500.f);

        // This should not happen either, but make sure our state can not get persistently broken
        // in case of corruption. Set to 0 as a last resort (may lead to a hard stop).
        if (!isfinite(pwm_))
            pwm_ = 0.f;

        for (bobbycar::protocol::serial::MotorState &motor : motors())
        {
            const auto pair = split(profileSettings.mickMode.modelMode);
            motor.ctrlTyp = pair.first;
            motor.ctrlMod = pair.second;
            motor.pwm = pwm_;
            motor.cruiseCtrlEna = false;
            motor.nCruiseMotTgt = 0;
        }
    }

    fixCommonParams();

    sendCommands();
}
