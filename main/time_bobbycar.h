#pragma once

#include "sdkconfig.h"

// 3rdparty lib includes
#include <espchrono.h>

espchrono::time_zone get_default_timezone() noexcept;

#ifdef FEATURE_NTP
void initTime();
void updateTime();
#endif
