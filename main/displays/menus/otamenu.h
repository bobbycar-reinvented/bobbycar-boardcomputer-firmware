#pragma once

// local includes
#include "displays/bobbymenudisplay.h"

class OtaMenu : public BobbyMenuDisplay
{
public:
    OtaMenu();

    std::string text() const override;

    void back() override;
};
