#pragma once

// local includes
#include "displays/bobbymenudisplay.h"

class NetworkSettingsMenu : public BobbyMenuDisplay
{
public:
    NetworkSettingsMenu();

    std::string text() const override;
    void back() override;
};
