#pragma once

// system includes
#include <cstdint>

// local includes
#include <bobbytypesafeenum.h>

typedef struct {
    uint16_t minVoltage;
    uint16_t maxVoltage;
} CalibrationPointVoltages;

// battery curves
#define PERCENTAGE(higherVoltage,lowerVoltage,fromAh,toAh) \
if (cellVoltage >= lowerVoltage && cellVoltage <= higherVoltage) \
        return 100 * (expected_ah - cpputils::mapValue<float>(cellVoltage, higherVoltage, lowerVoltage, fromAh, toAh)) / expected_ah;

#define GET_MINIMUM_VOLTAGE(higherVoltage,lowerVoltage,fromAh,toAh) \
    if (expected_ah >= toAh) \
        return lowerVoltage;

#define GET_MAXIMUM_VOLTAGE(higherVoltage,lowerVoltage,fromAh,toAh) \
    if (fromAh == 0) \
        return higherVoltage;

#define GET_MINIMUM_BAT_VOLTAGE(higherVoltage,lowerVoltage,fromAh,toAh) \
    if (lowerVoltage < minimumVoltage) \
        minimumVoltage = lowerVoltage;

#define GET_MAXIMUM_BAT_VOLTAGE(higherVoltage,lowerVoltage,fromAh,toAh) \
    if (fromAh == 0) \
        return higherVoltage;


// All curves here have to follow the same order (highest-voltage first)
// as some functions require this to display data in correct order

// 22P
#define BAT_MIN_AH_22P 2.2
#define BAT_CURVE_22P(func) \
    func(4.15, 4.04, 0, 0.25) \
    func(4.04, 3.95, 0.25, 0.5) \
    func(3.95, 3.86, 0.5, 0.75) \
    func(3.86, 3.74, 0.75, 1.0) \
    func(3.74, 3.64, 1.0, 1.25) \
    func(3.64, 3.59, 1.25, 1.5) \
    func(3.59, 3.54, 1.5, 1.75) \
    func(3.54, 3.43, 1.75, 2.0) \
    func(3.43, 3.35, 2.0, 2.1) \
    func(3.35, 2.50, 2.1, 2.2)

// MH1
#define BAT_MIN_AH_MH1 3.2
#define BAT_CURVE_MH1(func) \
    func(4.15, 4.09, 0, 0.25) \
    func(4.09, 4.04, 0.25, 0.5) \
    func(4.04, 3.95, 0.5, 0.75) \
    func(3.95, 3.88, 0.75, 1.0) \
    func(3.88, 3.79, 1.0, 1.25) \
    func(3.79, 3.70, 1.25, 1.5) \
    func(3.70, 3.65, 1.5, 1.75) \
    func(3.65, 3.60, 1.75, 2.0) \
    func(3.60, 3.56, 2.0, 2.25) \
    func(3.56, 3.50, 2.25, 2.5) \
    func(3.50, 3.40, 2.5, 2.75) \
    func(3.40, 3.30, 2.75, 3.0) \
    func(3.30, 2.5, 3.0, 3.2)

// HG2
#define BAT_MIN_AH_HG2 3.0
#define BAT_CURVE_HG2(func) \
    func(4.15, 4.08, 0, 0.25) \
    func(4.08, 4.01, 0.25, 0.5) \
    func(4.01, 3.92, 0.5, 0.75) \
    func(3.92, 3.84, 0.75, 1.0) \
    func(3.84, 3.75, 1.0, 1.25) \
    func(3.75, 3.67, 1.25, 1.5) \
    func(3.67, 3.62, 1.5, 1.75) \
    func(3.62, 3.55, 1.75, 2.0) \
    func(3.55, 3.44, 2.0, 2.25) \
    func(3.44, 3.30, 2.25, 2.5) \
    func(3.30, 3.05, 2.5, 2.75) \
    func(3.05, 2.50, 2.75, 3.0)

// VTC5
#define BAT_MIN_AH_VTC5 2.6
#define BAT_CURVE_VTC5(func) \
    func(4.15, 4.08, 0, 0.25) \
    func(4.08, 3.98, 0.25, 0.5) \
    func(3.98, 3.89, 0.5, 0.75) \
    func(3.89, 3.79, 0.75, 1.0) \
    func(3.79, 3.71, 1.0, 1.25) \
    func(3.71, 3.64, 1.25, 1.5) \
    func(3.64, 3.53, 1.5, 1.75) \
    func(3.53, 3.44, 1.75, 2.0) \
    func(3.44, 3.20, 2.0, 2.25) \
    func(3.20, 2.80, 2.25, 2.5) \
    func(2.80, 2.50, 2.5, 2.60)

// BAK_25R
#define BAT_MIN_AH_BAK_25R 2.5
#define BAT_CURVE_25R(func) \
    func(4.15, 4.06, 0, 0.25) \
    func(4.06, 3.96, 0.25, 0.5) \
    func(3.96, 3.88, 0.5, 0.75) \
    func(3.88, 3.77, 0.75, 1) \
    func(3.77, 3.68, 1, 1.25) \
    func(3.68, 3.62, 1.25, 1.5) \
    func(3.62, 3.56, 1.5, 1.75) \
    func(3.56, 3.47, 1.75, 2) \
    func(3.47, 3.31, 2, 2.25) \
    func(3.31, 2.50, 2.25, 2.5)

// HE4
#define BAT_MIN_AH_HE4 2.3
#define BAT_CURVE_HE4(func) \
    func(4.15, 4.02, 0, 0.25) \
    func(4.02, 3.91, 0.25, 0.5) \
    func(3.91, 3.81, 0.5, 0.75) \
    func(3.81, 3.72, 0.75, 1) \
    func(3.72, 3.61, 1, 1.25) \
    func(3.61, 3.62, 1.25, 1.5) \
    func(3.62, 3.53, 1.5, 1.75) \
    func(3.53, 3.45, 1.75, 2) \
    func(3.45, 3.21, 2, 2.25) \
    func(3.21, 2.80, 2.25, 2.3)

#define BatteryCellTypeValues(x) \
    x(_22P) \
    x(HG2) \
    x(MH1) \
    x(VTC5) \
    x(BAK_25R) \
    x(HE4)
DECLARE_BOBBYTYPESAFE_ENUM(BatteryCellType, : uint8_t, BatteryCellTypeValues)

float getBatteryPercentage(float batVoltage, BatteryCellType cellType);

float getRemainingWattHours();

float getBatteryWattHours();

float getMinBatCellVoltage(BatteryCellType cellType);
float getMaxBatCellVoltage(BatteryCellType cellType);

std::string getBatteryPercentageString();

std::string getBatteryRemainingWattHoursString();

std::string getRemainingRangeString();

std::string getBatteryDebugString();

std::string getBatteryAdvancedPercentageString();

float getPercentageByWh(float wh);
float getTarget_mAh();

uint8_t count_curve_points(BatteryCellType cellType);

std::optional<CalibrationPointVoltages> get_point_n_voltages(BatteryCellType cellType, uint8_t num);

namespace battery {
extern std::optional<float> bootBatPercentage;
extern std::optional<float> bootBatWh;
}
