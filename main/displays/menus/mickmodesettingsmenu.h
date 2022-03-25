#pragma once

// local includes
#include "displays/bobbymenudisplay.h"

class MickModeSettingsMenu : public BobbyMenuDisplay
{
public:
    MickModeSettingsMenu();

    std::string text() const override;

    void back() override;
};
