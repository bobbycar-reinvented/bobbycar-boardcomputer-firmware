#include "battery.h"

// 3rdparty lib includes
#include <cpputils.h>
#include <fmt/core.h>

// local includes
#include "drivingstatistics.h"
#include "globals.h"
#include "newsettings.h"
#ifdef FEATURE_ESPNOW_BMS
#include "espnowbms.h"
#endif

namespace bobby::battery {

std::optional<float> bootBatPercentage;
std::optional<float> bootBatWh;

float getBatteryPercentage(float batVoltage, BatteryCellType cellType)
{
    const float cellVoltage = batVoltage / configs.battery.cellsSeries.value();

    switch (cellType)
    {
    case BatteryCellType::_22P:
    {
        const float expected_ah = BAT_MIN_AH_22P;
        if (cellVoltage > 4.15f)
            return 100.f;
        BAT_CURVE_22P(PERCENTAGE);
        break;
    }
    case BatteryCellType::MH1:
    {
        const float expected_ah = BAT_MIN_AH_MH1;
        if (cellVoltage > 4.15f)
            return 100.f;
        BAT_CURVE_MH1(PERCENTAGE);
        break;
    }
    case BatteryCellType::HG2:
    {
        const float expected_ah = BAT_MIN_AH_HG2;
        if (cellVoltage > 4.15f)
            return 100.f;
        BAT_CURVE_HG2(PERCENTAGE);
        break;
    }
    case BatteryCellType::VTC5:
    {
        const float expected_ah = BAT_MIN_AH_VTC5;
        if (cellVoltage > 4.15f)
            return 100.f;
        BAT_CURVE_VTC5(PERCENTAGE);
        break;
    }
    case BatteryCellType::BAK_25R:
    {
        const float expected_ah = BAT_MIN_AH_BAK_25R;
        if(cellVoltage > 4.15f){
            return 100.f;
        }
        BAT_CURVE_25R(PERCENTAGE);
        break;
    }
    case BatteryCellType::HE4:
    {
        const float expected_ah = BAT_MIN_AH_HE4;
        if(cellVoltage > 4.15f){
            return 100.f;
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
        return (target_mah / 1000.f) * 3.7f * configs.battery.cellsParallel.value() * configs.battery.cellsSeries.value() * (getBatteryPercentage(*avgVoltage, configs.battery.cellType.value()) / 100);
    }
    else
        return 0.f;
}

float getPercentageByWh(float wh)
{
    const float maxWh = (getTarget_mAh() / 1000.f) * 3.7f * configs.battery.cellsParallel.value() * configs.battery.cellsSeries.value();
    return maxWh / wh;
}

float getBatteryWattHours()
{
    return (getTarget_mAh() / 1000.f) * 3.7f * configs.battery.cellsParallel.value() * configs.battery.cellsSeries.value();
}

float getTarget_mAh()
{
    switch (configs.battery.cellType.value())
    {
    case BatteryCellType::_22P:
        return 2200;
    case BatteryCellType::HG2:
        return 3000;
    case BatteryCellType::MH1:
        return 3200;
    case BatteryCellType::VTC5:
        return 2600;
    case BatteryCellType::BAK_25R:
        return 2500;
    case BatteryCellType::HE4:
        return 2300;
    default:
        return 2000;
    }
}

std::string getBatteryPercentageString()
{
    if (const auto avgVoltage = controllers.getAvgVoltage(); avgVoltage)
    {
        std::string output = fmt::format("Battery: {:.1f}%", getBatteryPercentage(*avgVoltage, configs.battery.cellType.value()));
        return output;
    }
    else if (espnowbms::ant_bms_data.constructed())
    {
        std::string output = fmt::format("Battery: {:.1f}%", espnowbms::ant_bms_data->state_of_charge);
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
    return fmt::format("{:.1f} km", getRemainingWattHours() / configs.battery.watthoursPerKilometer.value());
}

std::string getBatteryDebugString()
{
    if (const auto avgVoltage = controllers.getAvgVoltage(); avgVoltage)
    {
        return fmt::format("{:.1f}V {}A", *avgVoltage, sumCurrent);
    }
    return "No Battery";
}

float getMinBatCellVoltage(BatteryCellType cellType) {
    float minimumVoltage = std::numeric_limits<float>::max();
    switch (cellType)
    {
    case BatteryCellType::_22P:
    {
        BAT_CURVE_22P(GET_MINIMUM_BAT_VOLTAGE);
        break;
    }
    case BatteryCellType::HG2:
    {
        BAT_CURVE_HG2(GET_MINIMUM_BAT_VOLTAGE);
        break;
    }
    case BatteryCellType::MH1:
    {
        BAT_CURVE_MH1(GET_MINIMUM_BAT_VOLTAGE);
        break;
    }
    case BatteryCellType::VTC5:
    {
        BAT_CURVE_VTC5(GET_MINIMUM_BAT_VOLTAGE);
        break;
    }
    case BatteryCellType::BAK_25R:
    {
        BAT_CURVE_25R(GET_MINIMUM_BAT_VOLTAGE);
        break;
    }
    case BatteryCellType::HE4:
    {
        BAT_CURVE_HE4(GET_MINIMUM_BAT_VOLTAGE);
        break;
    }
    default:
        return 0.f;
    }
    return minimumVoltage;
}

float getMaxBatCellVoltage(BatteryCellType cellType)
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

uint8_t count_curve_points(BatteryCellType cellType)
{
#define COUNT_CURVE_POINTS(higherVoltage,lowerVoltage,fromAh,toAh) \
    count++;

    uint8_t count = 0;
    switch (cellType)
    {
        case BatteryCellType::_22P:
        {
            BAT_CURVE_22P(COUNT_CURVE_POINTS);
            break;
        }
        case BatteryCellType::HG2:
        {
            BAT_CURVE_HG2(COUNT_CURVE_POINTS);
            break;
        }
        case BatteryCellType::MH1:
        {
            BAT_CURVE_MH1(COUNT_CURVE_POINTS);
            break;
        }
        case BatteryCellType::VTC5:
        {
            BAT_CURVE_VTC5(COUNT_CURVE_POINTS);
            break;
        }
        case BatteryCellType::BAK_25R:
        {
            BAT_CURVE_25R(COUNT_CURVE_POINTS);
            break;
        }
        case BatteryCellType::HE4:
        {
            BAT_CURVE_HE4(COUNT_CURVE_POINTS);
            break;
        }
    }
    return count;
}

std::optional<CalibrationPointVoltages> get_point_n_voltages(BatteryCellType cellType, uint8_t num)
{
    #define GET_POINT_N_VOLTAGES(higherVoltage,lowerVoltage,fromAh,toAh) \
        if (count == num) { \
            uint16_t minVoltage = (lowerVoltage) * 100; \
            uint16_t maxVoltage = (higherVoltage) * 100; \
            return CalibrationPointVoltages{ .minVoltage=minVoltage, .maxVoltage=maxVoltage }; \
        } \
        count++;

    uint8_t count = 0;
    switch (cellType)
    {
        case BatteryCellType::_22P:
        {
            BAT_CURVE_22P(GET_POINT_N_VOLTAGES);
            break;
        }
        case BatteryCellType::HG2:
        {
            BAT_CURVE_HG2(GET_POINT_N_VOLTAGES);
            break;
        }
        case BatteryCellType::MH1:
        {
            BAT_CURVE_MH1(GET_POINT_N_VOLTAGES);
            break;
        }
        case BatteryCellType::VTC5:
        {
            BAT_CURVE_VTC5(GET_POINT_N_VOLTAGES);
            break;
        }
        case BatteryCellType::BAK_25R:
        {
            BAT_CURVE_25R(GET_POINT_N_VOLTAGES);
            break;
        }
        case BatteryCellType::HE4:
        {
            BAT_CURVE_HE4(GET_POINT_N_VOLTAGES);
            break;
        }
    }
    return std::nullopt;
}

}
