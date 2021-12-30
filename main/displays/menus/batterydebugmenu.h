#pragma once

// Local includes
#include "displays/bobbymenudisplay.h"

class BatteryDebugMenu : public BobbyMenuDisplay
{
public:
    BatteryDebugMenu();

    std::string text() const override;

    void back() override;
};
