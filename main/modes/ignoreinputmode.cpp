#include "ignoreinputmode.h"

// local includes
#include "globals.h"
#include "utils.h"

namespace bobby {

void IgnoreInputMode::update()
{
    for (bobbycar::protocol::serial::MotorState &motor : motors())
    {
        motor.ctrlTyp = m_ctrlTyp;
        motor.ctrlMod = m_ctrlMod;
        motor.pwm = m_pwm;
        motor.cruiseCtrlEna = false;
        motor.nCruiseMotTgt = 0;
    }
}

} // namespace bobby
