#pragma once

// local includes
#include "bobbytypesafeenum.h"
#include "modeinterface.h"
#include "modes/ignoreinputmode.h"

#define SetupStepValues(x) \
    x(INFORMATION) \
    x(BASIC_BUTTONS) \
    x(CALIBRATE_POTIS)

DECLARE_BOBBYTYPESAFE_ENUM(SetupStep, : uint8_t, SetupStepValues);

namespace setup {
extern bool currently_locked;
extern ModeInterface* oldMode;
extern IgnoreInputMode setup_mode;

void lock();
void unlock();
bool isLocked();
} // namespace setup
