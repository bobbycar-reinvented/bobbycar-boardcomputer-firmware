#pragma once

// system includes
#include <optional>

// 3rdparty lib includes
#include <espchrono.h>

namespace bobby::blinker {

extern std::optional<espchrono::millis_clock::time_point> blinker_last_time_sent;

extern std::optional<espchrono::millis_clock::time_point> brake_last_time_sent;

void handle_blinker();

} // namespace bobby::blinker
