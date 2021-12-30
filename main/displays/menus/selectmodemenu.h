#pragma once

// local includes
#include "displays/bobbymenudisplay.h"

class SelectModeMenu : public BobbyMenuDisplay
{
    using Base = BobbyMenuDisplay;

public:
    SelectModeMenu();

    std::string text() const override;

    void start() override;
    void back() override;
};
