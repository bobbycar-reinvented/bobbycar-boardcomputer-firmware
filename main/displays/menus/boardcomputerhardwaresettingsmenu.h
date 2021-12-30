#pragma once

// local includes
#include "displays/bobbymenudisplay.h"

class BoardcomputerHardwareSettingsMenu : public BobbyMenuDisplay
{
public:
    BoardcomputerHardwareSettingsMenu();

    std::string text() const override;

    void back() override;
};
