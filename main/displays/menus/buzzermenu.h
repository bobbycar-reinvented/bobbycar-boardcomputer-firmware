#pragma once

// local includes
#include "displays/bobbymenudisplay.h"

class BuzzerMenu : public BobbyMenuDisplay
{
public:
    BuzzerMenu();

    std::string text() const override;

    void back() override;
};
