#pragma once

// 3rdparty lib includes
#include <fmt/core.h>
#include <cpptypesafeenum.h>

// local includes
#include "globals.h"
#include "cpputils.h"

#define BatteryCellTypeValues(x) \
    x(_22P) \
    x(HG2) \
    x(MH1) \
    x(VTC5)
DECLARE_TYPESAFE_ENUM(BatteryCellType, : uint8_t, BatteryCellTypeValues)

namespace {
float battery_percentage = 42.f;

std::string getBatteryPercentageString()
{
    std::string output = fmt::format("Battery: {:.1f}%", battery_percentage);
    return output;
}

std::string getBatteryCellTypeString()
{
    return fmt::format("Cells: {}", toString(BatteryCellType(settings.battery.cellType)));
}
} // namespace
