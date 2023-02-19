#include "ledstripblinkactions.h"

// local includes
#include "ledstrip.h"
#include "ledstripdefines.h"

using namespace espgui;

namespace bobby {

using namespace ledstrip;

void LedstripAnimationBlinkNoneAction::triggered()
{
    blinkAnimation = LEDSTRIP_OVERWRITE_NONE;
}

#ifndef LEDSTRIP_WRONG_DIRECTION

void LedstripAnimationBlinkLeftAction::triggered()
{
    blinkAnimation = LEDSTRIP_OVERWRITE_BLINKLEFT;
}

#else
void LedstripAnimationBlinkLeftAction::triggered()
{
    blinkAnimation = LEDSTRIP_OVERWRITE_BLINKRIGHT;
}
#endif

#ifndef LEDSTRIP_WRONG_DIRECTION

void LedstripAnimationBlinkRightAction::triggered()
{
    blinkAnimation = LEDSTRIP_OVERWRITE_BLINKRIGHT;
}

#else
void LedstripAnimationBlinkRightAction::triggered()
{
    blinkAnimation = LEDSTRIP_OVERWRITE_BLINKLEFT;
}
#endif

void LedstripAnimationBlinkBothAction::triggered()
{
    blinkAnimation = LEDSTRIP_OVERWRITE_BLINKBOTH;
}

} // namespace bobby
