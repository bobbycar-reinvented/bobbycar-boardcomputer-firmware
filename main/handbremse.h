#pragma once

// system
#include <cstdint>
#include <optional>

// 3rdparty lib includes
#include <espchrono.h>

// local includes
#include "enums.h"

namespace handbremse {

extern bool angezogen;
extern bool finishedMotorUpdate;
extern std::optional<espchrono::millis_clock::time_point> releaseTimer;
extern std::optional<espchrono::millis_clock::time_point> wishTimer;
extern std::optional<espchrono::millis_clock::time_point> standStillFirstDetected;
extern std::optional<espchrono::millis_clock::time_point> lastAutoRelease;

enum StateWish {
    none,
    release,
    brake
};

extern StateWish stateWish;
} // namespace
