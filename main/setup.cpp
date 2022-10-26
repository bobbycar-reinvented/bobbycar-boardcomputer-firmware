#include "setup.h"

// local includes
#include "globals.h"

namespace setup {
bool currently_locked;
ModeInterface* oldMode;
IgnoreInputMode setup_mode{0, bobbycar::protocol::ControlType::FieldOrientedControl, bobbycar::protocol::ControlMode::Torque};

void lock()
{
    if (currently_locked)
        return;

    oldMode = currentMode;
    currentMode = &setup_mode;
}

void unlock()
{
    if (!currently_locked)
        return;

    if (currentMode == &setup_mode)
    {
        // to avoid crash after deconstruction
        setup_mode.stop();
        lastMode = nullptr;

        currentMode = oldMode;
    }
}

bool isLocked()
{
    return currently_locked;
}
} // namespace setup
