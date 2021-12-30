#pragma once

// local includes
#include "displays/bobbymenudisplay.h"

class PresetsMenu : public BobbyMenuDisplay
{
public:
    PresetsMenu();

    std::string text() const override;

    void back() override;
};
