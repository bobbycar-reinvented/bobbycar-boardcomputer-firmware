#pragma once

// local includes
#include "displays/bobbymenudisplay.h"

class WifiStaSettingsMenu : public BobbyMenuDisplay
{
public:
    WifiStaSettingsMenu();

    std::string text() const override;
    void back() override;
};
