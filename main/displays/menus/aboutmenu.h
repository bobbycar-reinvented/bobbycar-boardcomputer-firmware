#pragma once

// local includes
#include "displays/bobbymenudisplay.h"
#include "texts.h"

class AboutMenu :
    public BobbyMenuDisplay,
    public espgui::StaticText<TEXT_ABOUT>
{
public:
    AboutMenu();

    void back() override;
};
