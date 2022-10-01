#pragma once

// local includes
#include "displays/bobbymenudisplay.h"

class RecoveryMenu : public BobbyMenuDisplay
{
    using Base = BobbyMenuDisplay;
public:
    RecoveryMenu();

    std::string text() const override;

    void back() override {}

};
