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
        lastUpdate_ = now;

        float alpha = 1.f - expf(-timeDelta / profileSettings.mickMode.smoothing);

        float gasOf1500 = *gas * 1500.f / 1000.f;
        float brakeOf1500 = *brems * 1500.f / 1000.f;
        float controlInput = gasOf1500 - brakeOf1500;

        pwm_ = pwm_ * (1.f-alpha) + controlInput * alpha;
        // Should be in this range anyway
        pwm_ = std::clamp(pwm_, -1500.f, 1500.f);

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
