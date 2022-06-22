#pragma once

#include "globals.h"
#include "utils.h"
#include "softpwmlimiter.h"
#include "ble_bobby.h"

namespace motor_pwm_limiter {
    void update() {
        if (!configs.bleSettings.bleFenceEnabled.value() || pServer->getPeerDevices().size()) {
            soft_pwm_limiter::trigger = false;
            soft_pwm_limiter::update(1500.f);
            return;
        }

        soft_pwm_limiter::trigger = true;

        auto mot = motors();
        int max_pwm = 0;
        for (bobbycar::protocol::serial::MotorState &motor : mot) {
            max_pwm = std::max(max_pwm, std::abs(motor.pwm));
        }

        // Scale PWM proportionally to avoid loss of steering in case of wheelchair or RC mode
        soft_pwm_limiter::update(max_pwm);
        float new_max = soft_pwm_limiter::limit(max_pwm);
        float ratio;
        if (max_pwm > 0.f)
            ratio = new_max / max_pwm;
        else
            ratio = 0.f;

        // Should not happen
        if (ratio > 1.f)
            ratio = 1.f;

        for (bobbycar::protocol::serial::MotorState &motor : mot) {
            motor.pwm = motor.pwm * ratio;
        }
    }
}
