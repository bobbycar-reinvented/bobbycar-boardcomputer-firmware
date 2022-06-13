#pragma once

// system includes
#include <cstdint>
#include <optional>

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
#define BAT_MIN_AH_22P 2.2f
#define BAT_CURVE_22P(func) \
    func(4.15f, 4.04f, 0.00f, 0.25f) \
    func(4.04f, 3.95f, 0.25f, 0.50f) \
    func(3.95f, 3.86f, 0.50f, 0.75f) \
    func(3.86f, 3.74f, 0.75f, 1.00f) \
    func(3.74f, 3.64f, 1.00f, 1.25f) \
    func(3.64f, 3.59f, 1.25f, 1.50f) \
    func(3.59f, 3.54f, 1.50f, 1.75f) \
    func(3.54f, 3.43f, 1.75f, 2.00f) \
    func(3.43f, 3.35f, 2.00f, 2.10f) \
    func(3.35f, 2.50f, 2.10f, 2.20f)

// MH1
#define BAT_MIN_AH_MH1 3.2f
#define BAT_CURVE_MH1(func) \
    func(4.15f, 4.09f, 0.00f, 0.25f) \
    func(4.09f, 4.04f, 0.25f, 0.50f) \
    func(4.04f, 3.95f, 0.50f, 0.75f) \
    func(3.95f, 3.88f, 0.75f, 1.00f) \
    func(3.88f, 3.79f, 1.00f, 1.25f) \
    func(3.79f, 3.70f, 1.25f, 1.50f) \
    func(3.70f, 3.65f, 1.50f, 1.75f) \
    func(3.65f, 3.60f, 1.75f, 2.00f) \
    func(3.60f, 3.56f, 2.00f, 2.25f) \
    func(3.56f, 3.50f, 2.25f, 2.50f) \
    func(3.50f, 3.40f, 2.50f, 2.75f) \
    func(3.40f, 3.30f, 2.75f, 3.00f) \
    func(3.30f, 2.50f, 3.00f, 3.20f)

// HG2
#define BAT_MIN_AH_HG2 3.0f
#define BAT_CURVE_HG2(func) \
    func(4.15f, 4.08f, 0.00f, 0.25f) \
    func(4.08f, 4.01f, 0.25f, 0.50f) \
    func(4.01f, 3.92f, 0.50f, 0.75f) \
    func(3.92f, 3.84f, 0.75f, 1.00f) \
    func(3.84f, 3.75f, 1.00f, 1.25f) \
    func(3.75f, 3.67f, 1.25f, 1.50f) \
    func(3.67f, 3.62f, 1.50f, 1.75f) \
    func(3.62f, 3.55f, 1.75f, 2.00f) \
    func(3.55f, 3.44f, 2.00f, 2.25f) \
    func(3.44f, 3.30f, 2.25f, 2.50f) \
    func(3.30f, 3.05f, 2.50f, 2.75f) \
    func(3.05f, 2.50f, 2.75f, 3.00f)

// VTC5
#define BAT_MIN_AH_VTC5 2.6f
#define BAT_CURVE_VTC5(func) \
    func(4.15f, 4.08f, 0.00f, 0.25f) \
    func(4.08f, 3.98f, 0.25f, 0.50f) \
    func(3.98f, 3.89f, 0.50f, 0.75f) \
    func(3.89f, 3.79f, 0.75f, 1.00f) \
    func(3.79f, 3.71f, 1.00f, 1.25f) \
    func(3.71f, 3.64f, 1.25f, 1.50f) \
    func(3.64f, 3.53f, 1.50f, 1.75f) \
    func(3.53f, 3.44f, 1.75f, 2.00f) \
    func(3.44f, 3.20f, 2.00f, 2.25f) \
    func(3.20f, 2.80f, 2.25f, 2.50f) \
    func(2.80f, 2.50f, 2.50f, 2.60f)

// BAK_25R
#define BAT_MIN_AH_BAK_25R 2.5f
#define BAT_CURVE_25R(func) \
    func(4.15f, 4.06f, 0.00f, 0.25f) \
    func(4.06f, 3.96f, 0.25f, 0.50f) \
    func(3.96f, 3.88f, 0.50f, 0.75f) \
    func(3.88f, 3.77f, 0.75f, 1.00f) \
    func(3.77f, 3.68f, 1.00f, 1.25f) \
    func(3.68f, 3.62f, 1.25f, 1.50f) \
    func(3.62f, 3.56f, 1.50f, 1.75f) \
    func(3.56f, 3.47f, 1.75f, 2.00f) \
    func(3.47f, 3.31f, 2.00f, 2.25f) \
    func(3.31f, 2.50f, 2.25f, 2.50f)

// HE4
#define BAT_MIN_AH_HE4 2.3f
#define BAT_CURVE_HE4(func) \
    func(4.15f, 4.02f, 0.00f, 0.25f) \
    func(4.02f, 3.91f, 0.25f, 0.50f) \
    func(3.91f, 3.81f, 0.50f, 0.75f) \
    func(3.81f, 3.72f, 0.75f, 1.00f) \
    func(3.72f, 3.61f, 1.00f, 1.25f) \
    func(3.61f, 3.62f, 1.25f, 1.50f) \
    func(3.62f, 3.53f, 1.50f, 1.75f) \
    func(3.53f, 3.45f, 1.75f, 2.00f) \
    func(3.45f, 3.21f, 2.00f, 2.25f) \
    func(3.21f, 2.80f, 2.25f, 2.30f)

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
