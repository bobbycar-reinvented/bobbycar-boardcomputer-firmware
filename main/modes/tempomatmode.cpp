#include "tempomatmode.h"

// local includes
#include "globals.h"
#include "utils.h"
#include "defaultmode.h"

namespace bobby {

namespace modes {
TempomatMode tempomatMode;
} // namespace modes

void TempomatMode::start()
{
    Base::start();
    nCruiseMotTgt = avgSpeed;
}

void TempomatMode::update()
{
    if (!gas || !brems)
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
        if (*gas > 500. && *brems > 500.)
        {
            nCruiseMotTgt = 0;
            modes::defaultMode.waitForGasLoslass = true;
            modes::defaultMode.waitForBremsLoslass = true;
            currentMode = &modes::defaultMode;
            return;
        }

        nCruiseMotTgt += (*gas/1000.) - (*brems/1000.);

        for (bobbycar::protocol::serial::MotorState &motor : motors())
        {
            const auto pair = split(profileSettings.tempomatMode.modelMode);
            motor.ctrlTyp = pair.first;
            motor.ctrlMod = pair.second;
            motor.pwm = 0;
            motor.cruiseCtrlEna = true;
            motor.nCruiseMotTgt = nCruiseMotTgt;
        }
    }
}

} // namespace bobby
