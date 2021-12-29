#pragma once

// local includes
#include "displays/bobbymenudisplay.h"

class WifiStaConfigsMenu : public BobbyMenuDisplay
{
public:
    WifiStaConfigsMenu();

    std::string text() const override;
    void back() override;
};
