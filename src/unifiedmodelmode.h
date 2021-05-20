#pragma once

#include <utility>

#include <HardwareSerial.h>

#include "bobbycar-protocol/bobbycar-common.h"

namespace {
enum class UnifiedModelMode : uint8_t
{
    Commutation,
    Sinusoidal,
    FocVoltage,
    FocSpeed,
    FocTorque
};

std::pair<ControlType, ControlMode> split(UnifiedModelMode mode)
{
    switch (mode)
    {
    case UnifiedModelMode::Commutation: return std::make_pair(ControlType::Commutation, ControlMode::Voltage);
    case UnifiedModelMode::Sinusoidal: return std::make_pair(ControlType::Sinusoidal, ControlMode::Voltage);
    case UnifiedModelMode::FocVoltage: return std::make_pair(ControlType::FieldOrientedControl, ControlMode::Voltage);
    case UnifiedModelMode::FocSpeed: return std::make_pair(ControlType::FieldOrientedControl, ControlMode::Speed);
    case UnifiedModelMode::FocTorque: return std::make_pair(ControlType::FieldOrientedControl, ControlMode::Torque);
    }

    Serial.printf("Unknown UnifiedModelMode: %i\r\n", int(mode));

    return std::make_pair(ControlType::FieldOrientedControl, ControlMode::OpenMode);
}
}
