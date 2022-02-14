#include "tempomat.h"

namespace pwmomat {
std::optional<float> tempomat_pwm;
std::optional<espchrono::millis_clock::time_point> enabled_time;

WISH wish{WISH::NONE};
} // namespace pwmomat