#pragma once

// local includes
#include "displays/bobbymenudisplay.h"

class ControllerHardwareSettingsMenu : public BobbyMenuDisplay
{
public:
    ControllerHardwareSettingsMenu();

    std::string text() const override;

    void back() override;
};
