#pragma once

#include "sdkconfig.h"

// 3rdparty lib includes
#include <espchrono.h>

espchrono::time_zone get_default_timezone() noexcept;

namespace bobby::time {

void initTime();

void updateTime();

void time_set_now(espchrono::utc_clock::time_point now);

void calculate_sun();

} // namespace bobby::time

