#pragma once

// local includes
#include "displays/bobbymenudisplay.h"
#include "texts.h"

class InvertMenu :
    public BobbyMenuDisplay,
    public espgui::StaticText<TEXT_SETINVERTED>
{
public:
    InvertMenu();
    void back() override;
};
