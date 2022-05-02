#pragma once

// 3rdparty lib includes
#include <espchrono.h>

namespace bobbyblinker {
    extern std::optional<espchrono::millis_clock::time_point> blinker_last_time_sent;
    void handle_blinker();
} // namespace bobbyhupe
