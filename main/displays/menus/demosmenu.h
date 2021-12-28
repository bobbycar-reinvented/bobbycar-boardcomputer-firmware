#pragma once

// local includes
#include "displays/bobbymenudisplay.h"
#include "texts.h"

class DemosMenu :
    public BobbyMenuDisplay,
    public espgui::StaticText<TEXT_DEMOS>
{
public:
    DemosMenu();

    void back() override;
};
