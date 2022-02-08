#pragma once

// system includes
#include <cstdint>

// local includes
#include <bobbytypesafeenum.h>

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

std::string getBatteryPercentageString();

std::string getBatteryRemainingWattHoursString();

std::string getBatteryCellTypeString();

std::string getRemainingRangeString();

std::string getBatteryDebugString();

std::string getBatteryAdvancedPercentageString();

float getPercentageByWh(float wh);
float getTarget_mAh();

namespace battery {
extern std::optional<float> bootBatPercentage;
extern std::optional<float> bootBatWh;
}
