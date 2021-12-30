#pragma once

// local includes
#include "displays/bobbymenudisplay.h"

class EnableMenu : public BobbyMenuDisplay
{
public:
    EnableMenu();

    std::string text() const override;

    void back() override;
};
