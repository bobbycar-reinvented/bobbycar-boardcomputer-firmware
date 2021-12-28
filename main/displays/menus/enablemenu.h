#pragma once

// local includes
#include "displays/bobbymenudisplay.h"
#include "texts.h"

using namespace espgui;

class EnableMenu :
    public BobbyMenuDisplay,
    public StaticText<TEXT_SETENABLED>
{
public:
    EnableMenu();
    void back() override;
};
