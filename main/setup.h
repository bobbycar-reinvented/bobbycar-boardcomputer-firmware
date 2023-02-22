#pragma once

// local includes
#include "enums.h"
#include "modeinterface.h"
#include "modes/ignoreinputmode.h"

namespace bobby::setup {
extern bool currently_locked;
extern ModeInterface* oldMode;
extern IgnoreInputMode setup_mode;

void lock();
void unlock();
bool isLocked();
} // namespace bobby::setup
