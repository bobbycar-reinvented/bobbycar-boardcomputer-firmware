#include "softpwmlimiter.h"

// system includes
#include <algorithm>

// 3rdparty lib includes
#include <espchrono.h>

namespace soft_pwm_limiter {
constexpr float MAX_LIMIT = 1500.f;

namespace {
float actual_limit = MAX_LIMIT;
bool active = false;
espchrono::millis_clock::time_point last_update;
} // namespace

bool trigger = false;

void update()
{
    using namespace std::chrono_literals;

    if (trigger)
    {
        const auto now = espchrono::millis_clock::now();
        if (!active)
        {
            last_update = now;
            active = true;
            return;
        }

        // int time_delta = std::chrono::floor<std::chrono::milliseconds>(now - last_update).count();
        int time_delta = espchrono::ago(last_update) / 1ms;
        last_update = now;
        time_delta = std::max(time_delta, 0);

        // Exit field weakening area ]1000, 1500] within 2 seconds
        actual_limit -= 500.f * time_delta / 2000.f;
        actual_limit = std::max(actual_limit, 0.f);
    }
    else
    {
        actual_limit = MAX_LIMIT;
        active = false;
    }
}

float limit(float pwm)
{
    return std::clamp(pwm, -actual_limit, actual_limit);
}

} // namespace soft_pwm_limiter
