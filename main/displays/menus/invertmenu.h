#pragma once

// local includes
#include "displays/bobbymenudisplay.h"
#include "texts.h"

using namespace espgui;

class InvertMenu :
    public MenuDisplay,
    public StaticText<TEXT_SETINVERTED>
{
public:
    InvertMenu();
    void back() override;
};
