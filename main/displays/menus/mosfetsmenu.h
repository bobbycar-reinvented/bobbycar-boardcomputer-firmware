#pragma once

#ifdef FEATURE_MOSFETS

// local includes
#include "displays/bobbymenudisplay.h"

class MosfetsMenu : public BobbyMenuDisplay
{
public:
    MosfetsMenu();

    std::string text() const override;

    void back() override;
};
#endif
