#pragma once

// local includes
#include "displays/bobbymenudisplay.h"

class WifiApSettingsMenu : public BobbyMenuDisplay
{
public:
    WifiApSettingsMenu();

    std::string text() const override;
    void back() override;
};
