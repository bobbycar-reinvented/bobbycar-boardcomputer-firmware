#pragma once

// system includes
#include <optional>

// 3rdparty lib includes
#include <espchrono.h>

namespace bobby::bobbyhupe {

extern bool hupe_state;

extern std::optional<espchrono::millis_clock::time_point> hupe_last_time_sent;

void handle_hupe();

void activate_hupe();

void deactivate_hupe();

void activate_compressor();

void deactivate_compressor();

void toggle_compressor();

} // namespace bobbyhupe
