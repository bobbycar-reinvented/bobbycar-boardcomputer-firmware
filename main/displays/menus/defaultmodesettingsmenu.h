#pragma once

// local includes
#include "displays/bobbymenudisplay.h"

class DefaultModeSettingsMenu : public BobbyMenuDisplay
{
public:
    DefaultModeSettingsMenu();

    std::string text() const override;

    void back() override;
};
