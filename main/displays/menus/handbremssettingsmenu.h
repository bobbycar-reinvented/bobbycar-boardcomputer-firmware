#pragma once

// local includes
#include "displays/bobbymenudisplay.h"

class HandbremsSettingsMenu : public BobbyMenuDisplay
{
public:
    HandbremsSettingsMenu();

    std::string text() const override;

    void back() override;
};
