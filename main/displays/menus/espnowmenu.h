#pragma once

// local includes
#include "displays/bobbymenudisplay.h"

class EspNowMenu : public BobbyMenuDisplay
{
public:
    EspNowMenu();

    std::string text() const override;

    void back() override;
};
