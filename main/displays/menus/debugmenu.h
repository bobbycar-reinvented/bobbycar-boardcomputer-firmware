#pragma once

// local includes
#include "displays/bobbymenudisplay.h"
#include "texts.h"

class DebugMenu :
    public BobbyMenuDisplay,
    public espgui::StaticText<TEXT_DEBUG>
{
public:
    DebugMenu();

    void back() override;
};
