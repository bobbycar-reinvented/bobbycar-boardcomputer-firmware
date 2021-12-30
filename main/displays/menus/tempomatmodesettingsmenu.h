#pragma once

// local includes
#include "displays/bobbymenudisplay.h"

class TempomatModeSettingsMenu : public BobbyMenuDisplay
{
public:
    TempomatModeSettingsMenu();

    std::string text() const override;

    void back() override;
};
