#pragma once

// local includes
#include "displays/bobbymenudisplay.h"

class LarsmModeSettingsMenu : public BobbyMenuDisplay
{
public:
    LarsmModeSettingsMenu();

    std::string text() const override;

    void back() override;
};
