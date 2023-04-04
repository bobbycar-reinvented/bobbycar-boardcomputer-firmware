#include "modes.h"

// local includes
#include "globals.h"
#include "motorpwmlimiter.h"
#include "utils.h"

namespace bobby {

void initDrivingMode()
{

}

void updateDrivingMode()
{
    if (lastMode != currentMode)
    {
        if (lastMode)
            lastMode->stop();
        lastMode = currentMode;
        if (currentMode)
            currentMode->start();
    }

    if (currentMode)
        currentMode->update();

    fixCommonParams();
    motor_pwm_limiter::update();

    // Last, send values to motor controllers
    if (!configs.emulateFeedback.value())
        sendCommands();
}

} // namespace bobby
