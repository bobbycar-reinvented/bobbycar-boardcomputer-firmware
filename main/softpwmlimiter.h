#pragma once

#include <algorithm>
#include <cmath>

#include <espchrono.h>

namespace soft_pwm_limiter {
    namespace {
        constexpr float MAX_LIMIT = 1500.f;
        //inline constexpr float TAU = 5000.f;

        inline float actual_limit = MAX_LIMIT;
        inline bool active = false;
        inline espchrono::millis_clock::time_point last_update;
    }

    inline bool trigger = false;

    void update(float current_pwm) {
        if (trigger) {
            auto now = espchrono::millis_clock::now();
            if (!active) {
                last_update = now;
                active = true;
                return;
            }

            float time_delta = std::chrono::floor<std::chrono::milliseconds>(now - last_update).count();
            last_update = now;
            time_delta = std::max(time_delta, 0.f);

            //float smoothness = expf(-time_delta / TAU);

            //actual_limit = actual_limit * smoothness;
            // Exit field weakening area (]1000, 1500]) within 2 seconds
            actual_limit -= 500.f * time_delta / 2000.f;
            actual_limit = std::max(actual_limit, 0.f);
            //if (current_pwm >= -1500.f && current_pwm <= 1500.f)
            //    actual_limit = std::min(actual_limit, std::abs(current_pwm));
        } else {
            actual_limit = MAX_LIMIT;
            active = false;
        }
    }

    float limit(float pwm) {
        return std::clamp(pwm, -actual_limit, actual_limit);
    }
}
