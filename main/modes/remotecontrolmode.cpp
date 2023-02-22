#include "remotecontrolmode.h"

// local includes
#include "globals.h"
#include "utils.h"
#include "defaultmode.h"

using namespace std::chrono_literals;

namespace bobby {

namespace modes {
RemoteControlMode remoteControlMode;
} // namespace modes

void RemoteControlMode::update()
{
    auto pair = split(profileSettings.remoteControlMode.modelMode);
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
            motor.ctrlTyp = pair.first;
            motor.ctrlMod = pair.second;
            motor.cruiseCtrlEna = false;
            motor.nCruiseMotTgt = 0;
        }

        controllers.front.command.left.pwm = m_remoteCommand->frontLeft;
        controllers.front.command.right.pwm = m_remoteCommand->frontRight;
        controllers.back.command.left.pwm = m_remoteCommand->backLeft;
        controllers.back.command.right.pwm = m_remoteCommand->backRight;
    }
}

void RemoteControlMode::setRemoteCommand(const ble::RemoteCommand &command)
{
    m_remoteCommand = command;
    m_timestamp = espchrono::millis_clock::now();
}

} // namespace bobby
