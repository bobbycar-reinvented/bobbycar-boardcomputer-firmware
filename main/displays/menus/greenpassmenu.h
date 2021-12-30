#pragma once

// local includes
#include "displays/bobbymenudisplay.h"

class GreenPassMenu : public BobbyMenuDisplay
{
public:
    GreenPassMenu();

    std::string text() const override;

    void back() override;
};
