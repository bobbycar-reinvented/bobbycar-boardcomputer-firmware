#pragma once

// local includes
#include "displays/bobbymenudisplay.h"
#include "texts.h"

class TimersMenu :
    public BobbyMenuDisplay,
    public espgui::StaticText<TEXT_TIMERS>
{
public:
    TimersMenu();
    void back() override;
};
