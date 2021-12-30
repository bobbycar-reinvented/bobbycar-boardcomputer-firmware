#pragma once

// local includes
#include "displays/bobbymenudisplay.h"

class MotortestModeSettingsMenu : public BobbyMenuDisplay
{
public:
    MotortestModeSettingsMenu();

    std::string text() const override;

    void back() override;
};
