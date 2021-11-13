#pragma once

// 3rdparty lib includes
#include <fmt/core.h>
#include <cpptypesafeenum.h>
#include <cpputils.h>

// local includes
#include "globals.h"

#define BatteryCellTypeValues(x) \
    x(_22P) \
    x(HG2) \
    x(MH1) \
    x(VTC5) \
    x(BAK_25R)
DECLARE_TYPESAFE_ENUM(BatteryCellType, : uint8_t, BatteryCellTypeValues)

float getBatteryPercentage(float batVoltage, BatteryCellType cellType);

float getRemainingWattHours();

std::string getBatteryPercentageString();

std::string getBatteryRemainingWattHoursString();

std::string getBatteryCellTypeString();

std::string getRemainingRangeString();

std::string getBatteryDebugString();
