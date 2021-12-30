#pragma once

// local includes
#include "displays/bobbymenudisplay.h"

class CrashMenu : public BobbyMenuDisplay
{
public:
    CrashMenu();

    std::string text() const override;

    void back() override;
};
