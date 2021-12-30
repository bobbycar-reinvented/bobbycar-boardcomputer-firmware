#pragma once

// local includes
#include "displays/bobbymenudisplay.h"

class TimersMenu : public BobbyMenuDisplay
{
public:
    TimersMenu();

    std::string text() const override;

    void back() override;
};
