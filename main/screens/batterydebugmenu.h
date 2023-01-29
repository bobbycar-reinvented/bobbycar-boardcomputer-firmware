#pragma once

// Local includes
#include "guihelpers/bobbymenudisplay.h"

namespace bobby {

class BatteryDebugMenu : public BobbyMenuDisplay
{
public:
    BatteryDebugMenu();

    std::string title() const override;

    void back() override;
};

} // namespace bobby
