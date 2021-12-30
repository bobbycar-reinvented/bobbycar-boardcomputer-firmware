#pragma once

// local includes
#include "displays/bobbymenudisplay.h"

class LimitsSettingsMenu : public BobbyMenuDisplay
{
public:
    LimitsSettingsMenu();

    std::string text() const override;

    void back() override;
};
