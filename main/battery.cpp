#include "battery.h"

// 3rdparty lib includes
#include <fmt/core.h>
#include <cpputils.h>

// local includes
#include "drivingstatistics.h"
#include "globals.h"
#include "newsettings.h"

float getBatteryPercentage(float batVoltage, BatteryCellType cellType)
{
    const float cellVoltage = batVoltage / configs.battery.cellsSeries.value;

    switch (cellType)
    {
    case BatteryCellType::_22P:
    {
        const float expected_ah = BAT_MIN_AH_22P;
        if (cellVoltage > 4.15)
            return 100;
        BAT_CURVE_22P(PERCENTAGE);
        break;
    }
    case BatteryCellType::MH1:
    {
        const float expected_ah = BAT_MIN_AH_MH1;
        if (cellVoltage > 4.15)
            return 100;
        BAT_CURVE_MH1(PERCENTAGE);
        break;
    }
    case BatteryCellType::HG2:
    {
        const float expected_ah = BAT_MIN_AH_HG2;
        if (cellVoltage > 4.15)
            return 100;
        BAT_CURVE_HG2(PERCENTAGE);
        break;
    }
    case BatteryCellType::VTC5:
    {
        const float expected_ah = BAT_MIN_AH_VTC5;
        if (cellVoltage > 4.15)
            return 100;
        BAT_CURVE_VTC5(PERCENTAGE);
        break;
    }
    case BatteryCellType::BAK_25R:
    {
        const float expected_ah = BAT_MIN_AH_BAK_25R;
        if(cellVoltage > 4.15){
            return 100;
        }
        BAT_CURVE_25R(PERCENTAGE);
        break;
    }
    case BatteryCellType::HE4:
    {
        const float expected_ah = BAT_MIN_AH_HE4;
        if(cellVoltage > 4.15){
            return 100;
        }
        BAT_CURVE_HE4(PERCENTAGE);
        break;
    }
    }
    return 0.f;
}

float getRemainingWattHours()
{
    float target_mah = getTarget_mAh();

    if (const auto avgVoltage = controllers.getAvgVoltage(); avgVoltage)
    {
        return (target_mah / 1000.f) * 3.7 * configs.battery.cellsParallel.value * configs.battery.cellsSeries.value * (getBatteryPercentage(*avgVoltage, BatteryCellType(configs.battery.cellType.value)) / 100);
    }
    else
        return 0.;
}

float getPercentageByWh(float wh)
{
    const float maxWh = (getTarget_mAh() / 1000.f) * 3.7 * configs.battery.cellsParallel.value * configs.battery.cellsSeries.value;
    return maxWh / wh;
}

float getBatteryWattHours()
{
    return (getTarget_mAh() / 1000.f) * 3.7 * configs.battery.cellsParallel.value * configs.battery.cellsSeries.value;
}

float getTarget_mAh()
{
    float target_mah = 2000; //default
    if(BatteryCellType(configs.battery.cellType.value) == BatteryCellType::_22P) target_mah = 2200;
    if(BatteryCellType(configs.battery.cellType.value) == BatteryCellType::HG2) target_mah = 3000;
    if(BatteryCellType(configs.battery.cellType.value) == BatteryCellType::MH1) target_mah = 3200;
    if(BatteryCellType(configs.battery.cellType.value) == BatteryCellType::VTC5) target_mah = 2600;
    if(BatteryCellType(configs.battery.cellType.value) == BatteryCellType::BAK_25R) target_mah = 2500;
    if(BatteryCellType(configs.battery.cellType.value) == BatteryCellType::HE4) target_mah = 2300;
    return target_mah;
}

std::string getBatteryPercentageString()
{
    if (const auto avgVoltage = controllers.getAvgVoltage(); avgVoltage)
    {
        std::string output = fmt::format("Battery: {:.1f}%", getBatteryPercentage(*avgVoltage, BatteryCellType(configs.battery.cellType.value)));
        return output;
    }
    else
        return "No Battery.";
}

std::string getBatteryAdvancedPercentageString()
{
    std::string output = fmt::format("Battery: {:.1f}%", getPercentageByWh(drivingStatistics.batteryWhEstimate));
    return output;
}

std::string getBatteryRemainingWattHoursString()
{
    return fmt::format("{:.1f}Wh", getRemainingWattHours());
}

std::string getRemainingRangeString()
{
    return fmt::format("{:.1f} km", getRemainingWattHours() / configs.battery.watthoursPerKilometer.value);
}

std::string getBatteryDebugString()
{
    if (const auto avgVoltage = controllers.getAvgVoltage(); avgVoltage)
    {
        return fmt::format("{:.1f}V {}A", *avgVoltage, sumCurrent);
    }
    return "No Battery";
}

float getMinBatVoltage(BatteryCellType cellType) {
    switch (cellType)
    {
    case BatteryCellType::_22P:
    {
        const float expected_ah = BAT_MIN_AH_22P;
        BAT_CURVE_22P(GET_MINIMUM_BAT_VOLTAGE);
        break;
    }
    case BatteryCellType::HG2:
    {
        const float expected_ah = BAT_MIN_AH_HG2;
        BAT_CURVE_HG2(GET_MINIMUM_BAT_VOLTAGE);
        break;
    }
    case BatteryCellType::MH1:
    {
        const float expected_ah = BAT_MIN_AH_MH1;
        BAT_CURVE_MH1(GET_MINIMUM_BAT_VOLTAGE);
        break;
    }
    case BatteryCellType::VTC5:
    {
        const float expected_ah = BAT_MIN_AH_VTC5;
        BAT_CURVE_VTC5(GET_MINIMUM_BAT_VOLTAGE);
        break;
    }
    case BatteryCellType::BAK_25R:
    {
        const float expected_ah = BAT_MIN_AH_BAK_25R;
        BAT_CURVE_25R(GET_MINIMUM_BAT_VOLTAGE);
        break;
    }
    case BatteryCellType::HE4:
    {
        const float expected_ah = BAT_MIN_AH_HE4;
        BAT_CURVE_HE4(GET_MINIMUM_BAT_VOLTAGE);
        break;
    }
    }
    return 0.f;
}

float getMaxBatVoltage(BatteryCellType cellType)
{
    switch (cellType)
    {
        case BatteryCellType::_22P:
        {
            BAT_CURVE_22P(GET_MAXIMUM_BAT_VOLTAGE);
            break;
        }
        case BatteryCellType::HG2:
        {
            BAT_CURVE_HG2(GET_MAXIMUM_BAT_VOLTAGE);
            break;
        }
        case BatteryCellType::MH1:
        {
            BAT_CURVE_MH1(GET_MAXIMUM_BAT_VOLTAGE);
            break;
        }
        case BatteryCellType::VTC5:
        {
            BAT_CURVE_VTC5(GET_MAXIMUM_BAT_VOLTAGE);
            break;
        }
        case BatteryCellType::BAK_25R:
        {
            BAT_CURVE_25R(GET_MAXIMUM_BAT_VOLTAGE);
            break;
        }
        case BatteryCellType::HE4:
        {
            BAT_CURVE_HE4(GET_MAXIMUM_BAT_VOLTAGE);
            break;
        }
    }
    return 0.f;
}

namespace battery {
std::optional<float> bootBatPercentage;
std::optional<float> bootBatWh;
}
