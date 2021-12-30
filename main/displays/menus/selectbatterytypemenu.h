#pragma once

// Local includes
#include "displays/bobbymenudisplay.h"

class BatteryTypeMenu : public BobbyMenuDisplay
{
public:
    BatteryTypeMenu();

    std::string text() const override;

    void back() override;
};
