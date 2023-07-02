#include "tempomat.h"

namespace pwmomat {
std::optional<float> tempomat_pwm;
std::optional<espchrono::millis_clock::time_point> enabled_time;

WISH wish{WISH::NONE};

void increase()
{
    // only if enabled
    if (!tempomat_pwm || *tempomat_pwm >= 1500.f)
        return;

    // increase
    tempomat_pwm = std::min(*tempomat_pwm + 10.f, 1500.f);
}

void decrease()
{
    // only if enabled
    if (!tempomat_pwm || *tempomat_pwm <= 0.f)
        return;

    // decrease
    tempomat_pwm = std::max(*tempomat_pwm - 10.f, 0.f);
}
} // namespace pwmomat
