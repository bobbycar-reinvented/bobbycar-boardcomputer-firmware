#pragma once

#ifdef FEATURE_ESPNOW_BMS

// system includes
#include <cstdint>
#include <optional>
#include <vector>

// 3rdparty lib includes
#include <ArduinoJson.h>
#include <espchrono.h>
#include <fmt/core.h>
#include <tl/expected.hpp>
#include <delayedconstruction.h>

// local includes
#include "bobbytypesafeenum.h"

#include "esp_log.h"

#define BatteryStatusValues(x) \
    x(Unknown) \
    x(Idle) \
    x(Charge) \
    x(Discharge) \
    x(Standby) \
    x(Error)

DECLARE_BOBBYTYPESAFE_ENUM(BatteryStatus, : uint8_t, BatteryStatusValues);

namespace bobby::espnowbms
{

enum class ChargeMosfetStatus
{
    Off = 0x00,
    On = 0x01,
    OverchargeProtection = 0x02,
    OverCurrentProtection = 0x03,
    BatteryFull = 0x04,
    TotalOverpressure = 0x05,
    BatteryOverTemperature = 0x06,
    MosfetOverTemperature = 0x07,
    AbnormalCurrent = 0x08,
    BalancedLineDroppedString = 0x09,
    MotherboardOverTemperature = 0x0A,
    Unknown0x0B = 0x0B,
    Unknown0x0C = 0x0C,
    DischargeMosfetAbnormality = 0x0D,
    Unknown0x0E = 0x0E,
    ManuallyTurnedOff = 0x0F,
};

enum class DischargeMosfetStatus
{
    Off = 0x00,
    On = 0x01,
    OverdischargeProtection = 0x02,
    OverCurrentProtection = 0x03,
    Unknown0x04 = 0x04,
    TotalPressureUndervoltage = 0x05,
    BatteryOverTemperature = 0x06,
    MosfetOverTemperature = 0x07,
    AbnormalCurrent = 0x08,
    BalancedLineDroppedString = 0x09,
    MotherboardOverTemperature = 0x0A,
    ChargeMosfetOn = 0x0B,
    ShortCircuitProtection = 0x0C,
    DischargeMosfetAbnormality = 0x0D,
    StartException = 0x0E,
    ManuallyTurnedOff = 0x0F,
};

enum class BalancerStatus
{
    Off = 0x00,
    ExceedsTheLimitEquilibrium = 0x01,
    ChargeDifferentialPressureBalance = 0x02,
    BalancedOverTemperature = 0x03,
    AutomaticEqualization = 0x04,
    Unknown0x05 = 0x05,
    Unknown0x06 = 0x06,
    Unknown0x07 = 0x07,
    Unknown0x08 = 0x08,
    Unknown0x09 = 0x09,
    MotherboardOverTemperature = 0x0A,
};

struct AntBmsData
{
    BatteryStatus battery_status;
    std::string battery_status_string;
    float power;
    float mosfet_temperature;
    float balancer_temperature;
    float total_voltage;
    float current;
    float state_of_charge;
    float state_of_health;
    float total_battery_capacity_setting;
    float capacity_remaining;
    float battery_cycle_capacity;
    uint32_t total_runtime;
    std::string total_runtime_formatted;
    std::vector<float> cell_voltages;
    std::vector<float> temperatures;
    uint32_t balanced_cell_bitmask;
    float max_cell_voltage;
    float max_voltage_cell;
    float min_cell_voltage;
    float min_voltage_cell;
    float delta_cell_voltage;
    float average_cell_voltage;
    float accumulated_discharging_capacity;
    float accumulated_charging_capacity;
    float accumulated_discharging_time;
    std::string accumulated_discharging_time_formatted;
    float accumulated_charging_time;
    std::string accumulated_charging_time_formatted;

    ChargeMosfetStatus charge_mosfet_status;
    std::string charge_mosfet_status_string;
    DischargeMosfetStatus discharge_mosfet_status;
    std::string discharge_mosfet_status_string;
    BalancerStatus balancer_status;
    std::string balancer_status_string;

    std::string hardware_version;
    std::string software_version;

    std::optional<espchrono::millis_clock::time_point> last_update;

    void parseDoc(const JsonDocument &doc)
    {
        last_update = espchrono::millis_clock::now();

        if (doc.containsKey("pwr"))
        {
            power = doc["pwr"].as<float>();
        }

        if (doc.containsKey("tvo"))
        {
            total_voltage = doc["tvo"].as<float>();
        }

        if (doc.containsKey("cur"))
        {
            current = doc["cur"].as<float>();
        }

        if (doc.containsKey("soc"))
        {
            state_of_charge = doc["soc"].as<float>();
        }

        if (doc.containsKey("cre"))
        {
            capacity_remaining = doc["cre"].as<float>();
        }

        if (doc.containsKey("bst"))
        {
            battery_status = static_cast<BatteryStatus>(doc["bst"].as<uint8_t>());
        }

        if (doc.containsKey("cms"))
        {
            charge_mosfet_status = static_cast<ChargeMosfetStatus>(doc["cms"].as<uint8_t>());
        }

        if (doc.containsKey("dms"))
        {
            auto as_str = doc["dms"].as<std::string>();

            battery_status_string = toString(static_cast<BatteryStatus>(doc["dms"].as<uint8_t>()));
            battery_status = static_cast<BatteryStatus>(doc["dms"].as<uint8_t>());
        }

        if (doc.containsKey("bst"))
        {
            auto as_str = doc["bst"].as<std::string>();

            if (auto parsed = parseBatteryStatus(as_str); parsed.has_value())
            {
                battery_status = parsed.value();
            }
            else
            {
                battery_status = BatteryStatus::Unknown;
            }
        }

        if (doc.containsKey("dcv"))
        {
            delta_cell_voltage = doc["dcv"].as<float>();
        }

        if (doc.containsKey("mcv"))
        {
            max_cell_voltage = doc["mcv"].as<float>();
        }

        if (doc.containsKey("miv"))
        {
            min_cell_voltage = doc["miv"].as<float>();
        }

        if (doc.containsKey("bte"))
        {
            balancer_temperature = doc["bte"].as<float>();
        }

        if (doc.containsKey("mot"))
        {
            mosfet_temperature = doc["mot"].as<float>();
        }

        if (doc.containsKey("soh"))
        {
            state_of_health = doc["soh"].as<float>();
        }

        if (doc.containsKey("tbc"))
        {
            total_battery_capacity_setting = doc["tbc"].as<float>();
        }

        if (doc.containsKey("bcc"))
        {
            battery_cycle_capacity = doc["bcc"].as<float>();
        }

        if (doc.containsKey("trt"))
        {
            total_runtime = doc["trt"].as<uint32_t>();
        }

        if (doc.containsKey("bcb"))
        {
            balanced_cell_bitmask = doc["bcb"].as<uint16_t>();
        }

        if (doc.containsKey("mvc"))
        {
            max_voltage_cell = doc["mvc"].as<uint8_t>();
        }

        if (doc.containsKey("mic"))
        {
            min_voltage_cell = doc["mic"].as<uint8_t>();
        }

        if (doc.containsKey("acc"))
        {
            accumulated_charging_capacity = doc["acc"].as<float>();
        }

        if (doc.containsKey("adt"))
        {
            accumulated_discharging_time = doc["adt"].as<float>();
        }

        if (doc.containsKey("act"))
        {
            accumulated_charging_time = doc["act"].as<float>();
        }

        if (doc.containsKey("acv"))
        {
            average_cell_voltage = doc["acv"].as<float>();
        }

        if (doc.containsKey("adc"))
        {
            accumulated_discharging_capacity = doc["adc"].as<float>();
        }

        if (doc.containsKey("css"))
        {
            charge_mosfet_status_string = doc["css"].as<std::string>();
        }

        if (doc.containsKey("dss"))
        {
            discharge_mosfet_status_string = doc["dss"].as<std::string>();
        }

        if (doc.containsKey("bss"))
        {
            balancer_status_string = doc["bss"].as<std::string>();
        }

        if (doc.containsKey("dtf"))
        {
            accumulated_discharging_time_formatted = doc["dtf"].as<std::string>();
        }

        if (doc.containsKey("ctf"))
        {
            accumulated_charging_time_formatted = doc["ctf"].as<std::string>();
        }

        if (doc.containsKey("hrd"))
        {
            hardware_version = doc["hrd"].as<std::string>();
        }

        if (doc.containsKey("sft"))
        {
            software_version = doc["sft"].as<std::string>();
        }

        if (doc.containsKey("trf"))
        {
            total_runtime_formatted = doc["trf"].as<std::string>();
        }

        if (doc.containsKey("vol"))
        {
            auto cell_voltages_json = doc["vol"].as<JsonArrayConst>();
            cell_voltages.clear();
            for (const auto &cell_voltage_json: cell_voltages_json)
            {
                cell_voltages.push_back(cell_voltage_json.as<float>());
            }
        }

        if (doc.containsKey("tmp"))
        {
            auto temperatures_json = doc["tmp"].as<JsonArrayConst>();
            temperatures.clear();
            for (const auto &temperature_json: temperatures_json)
            {
                temperatures.push_back(temperature_json.as<float>());
            }
        }
    }
};

extern cpputils::DelayedConstruction<AntBmsData> ant_bms_data;

void init();
void update();

void commandReceived(const std::string& command);
} // namespace bobby::espnowbms

#endif // FEATURE_ESPNOW_BMS
