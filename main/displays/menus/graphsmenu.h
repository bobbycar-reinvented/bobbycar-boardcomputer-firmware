#pragma once

// local includes
#include "displays/bobbymenudisplay.h"
#include "texts.h"

class GraphsMenu :
    public BobbyMenuDisplay,
    public espgui::StaticText<TEXT_GRAPHS>
{
public:
    GraphsMenu();

    void back() override;
};
