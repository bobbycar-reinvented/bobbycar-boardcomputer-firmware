#pragma once

// 3rdparty lib includes
#include <espchrono.h>

// local includes
#include "globals.h"

auto espchrono::local_clock::timezone() noexcept -> time_zone
{
    return time_zone{minutes32{settings.timeSettings.timezoneOffset}, settings.timeSettings.daylightSavingMode};
}
