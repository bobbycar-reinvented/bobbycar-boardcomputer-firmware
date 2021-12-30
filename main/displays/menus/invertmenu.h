#pragma once

// local includes
#include "displays/bobbymenudisplay.h"

class InvertMenu : public BobbyMenuDisplay
{
public:
    InvertMenu();

    std::string text() const override;

    void back() override;
};
