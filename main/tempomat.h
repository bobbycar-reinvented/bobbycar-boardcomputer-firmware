#pragma once

// system includes
#include <optional>

// 3rdparty lib includes
#include <espchrono.h>

namespace pwmomat {
extern std::optional<float> tempomat_pwm; // saved pwm
extern std::optional<espchrono::millis_clock::time_point> enabled_time;

enum class WISH : uint8_t {
    NONE,
    WISH_ENABLE,
    WISH_DISABLE,
};

extern WISH wish;

void increase();
void decrease();
} // namespace pwmomat
