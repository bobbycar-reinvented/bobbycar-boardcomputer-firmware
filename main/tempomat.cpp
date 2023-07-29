#include "tempomat.h"

// local includes
#include "newsettings.h"

namespace pwmomat {
std::optional<float> tempomat_pwm;
std::optional<espchrono::millis_clock::time_point> enabled_time;

WISH wish{WISH::NONE};

void increase()
{
    // only if enabled
    if (!tempomat_pwm || *tempomat_pwm >= 1450.f)
        return;

    // increase
    tempomat_pwm = std::min(*tempomat_pwm + configs.pwmomat_change_val.value(), 1450.f);
}

void decrease()
{
    // only if enabled
    if (!tempomat_pwm || *tempomat_pwm <= 0.f)
        return;

    // decrease
    tempomat_pwm = std::max(*tempomat_pwm - configs.pwmomat_change_val.value(), 0.f);
}

bool is_active()
{
    return tempomat_pwm.has_value();
}
} // namespace pwmomat
