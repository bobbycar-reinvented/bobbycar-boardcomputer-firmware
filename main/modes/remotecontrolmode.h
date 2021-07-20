#pragma once

// system includes
#include <cstdint>
#include <optional>

// 3rdparty lib includes
#include <espchrono.h>

// local includes
#include "bobbycar-common.h"

#include "modeinterface.h"
#include "globals.h"
#include "utils.h"
#include "defaultmode.h"

using namespace std::chrono_literals;

namespace {
struct RemoteCommand {
    int16_t frontLeft{};
    int16_t frontRight{};
    int16_t backLeft{};
    int16_t backRight{};
};

class RemoteControlMode : public ModeInterface
{
    using Base = ModeInterface;

public:
    void update() override;

    const char *displayName() const override { return "RemoteControl"; }

    void setCommand(const RemoteCommand &command);

    std::optional<RemoteCommand> m_remoteCommand;
    espchrono::millis_clock::time_point m_timestamp;
};

namespace modes {
RemoteControlMode remoteControlMode;
}

void RemoteControlMode::update()
{
    if (!m_remoteCommand || espchrono::ago(m_timestamp) > 500ms)
    {
        start();

        for (bobbycar::protocol::serial::MotorState &motor : motors())
        {
            motor.ctrlTyp = bobbycar::protocol::ControlType::FieldOrientedControl;
            motor.ctrlMod = bobbycar::protocol::ControlMode::OpenMode;
            motor.pwm = 0;
            motor.cruiseCtrlEna = false;
            motor.nCruiseMotTgt = 0;
        }
    }
    else
    {
        for (bobbycar::protocol::serial::MotorState &motor : motors())
        {
            motor.ctrlTyp = bobbycar::protocol::ControlType::FieldOrientedControl;
            motor.ctrlMod = bobbycar::protocol::ControlMode::Torque;
            motor.cruiseCtrlEna = false;
            motor.nCruiseMotTgt = 0;
        }

        controllers.front.command.left.pwm = m_remoteCommand->frontLeft;
        controllers.front.command.right.pwm = m_remoteCommand->frontRight;
        controllers.back.command.left.pwm = m_remoteCommand->backLeft;
        controllers.back.command.right.pwm = m_remoteCommand->backRight;
    }

    fixCommonParams();

    sendCommands();
}

void RemoteControlMode::setCommand(const RemoteCommand &command)
{
    m_remoteCommand = command;
    m_timestamp = espchrono::millis_clock::now();
}
}
