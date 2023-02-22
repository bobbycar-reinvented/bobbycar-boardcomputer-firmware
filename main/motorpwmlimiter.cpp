#include "motorpwmlimiter.h"

// local includes
#include "ble_bobby.h"
#include "globals.h"
#include "softpwmlimiter.h"
#include "utils.h"

namespace bobby::motor_pwm_limiter {

void update()
{
    if (!configs.bleSettings.bleEnabled.value() || !configs.bleSettings.bleFenceEnabled.value() || (ble::pServer && !ble::pServer->getPeerDevices().empty()))
    {
        soft_pwm_limiter::trigger = false;
        soft_pwm_limiter::update();
        return;
    }

    soft_pwm_limiter::trigger = true;

    const auto mot = motors();

    int max_pwm = 0;
    for (const bobbycar::protocol::serial::MotorState &motor : mot)
    {
        max_pwm = std::max(max_pwm, std::abs(motor.pwm));
    }

    // Scale PWM proportionally to avoid loss of steering in case of wheelchair or RC mode
    soft_pwm_limiter::update();

    float new_max = soft_pwm_limiter::limit(max_pwm);
    float ratio;

    if (max_pwm > 0.f)
        ratio = new_max / max_pwm;
    else
        ratio = 0.f;

    // Should not happen
    if (ratio > 1.f)
        ratio = 1.f;

    for (bobbycar::protocol::serial::MotorState &motor : mot)
    {
        motor.pwm *= ratio;
    }
}

} // namespace bobby::motor_pwm_limiter
