#pragma once

// local includes
#include "displays/bobbymenudisplay.h"
#include "texts.h"

using namespace espgui;

class CrashMenu :
    public BobbyMenuDisplay,
    public StaticText<TEXT_CRASHMENU>
{
public:
    CrashMenu();
    void back() override;
};
