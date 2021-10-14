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

float getBatteryPercentage(float batVoltage, BatteryCellType cellType)
{
    float percentage = 0;
    switch (cellType) {
        case BatteryCellType::_22P:
            break;
        case BatteryCellType::MH1:
            break;
        case BatteryCellType::HG2:
            break;
        case BatteryCellType::VTC5:
            break;
    }
    return percentage;
}

std::string getBatteryPercentageString()
{
    float avgVoltage = 0;
    for (auto &controller : controllers)
    {
        avgVoltage += controller.getCalibratedVoltage(settings.battery.applyCalibration);
    }
    avgVoltage = avgVoltage / controllers.size();

    std::string output = fmt::format("Battery: {:.1f}%", getBatteryPercentage(avgVoltage, BatteryCellType(settings.battery.cellType)));
    return output;
}

std::string getBatteryCellTypeString()
{
    return fmt::format("Cells: {}", toString(BatteryCellType(settings.battery.cellType)));
}
} // namespace
