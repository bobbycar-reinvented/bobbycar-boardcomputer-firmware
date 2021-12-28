#pragma once

// local includes
#include "displays/bobbymenudisplay.h"
#include "texts.h"

class SelectModeMenu :
    public BobbyMenuDisplay,
    public espgui::StaticText<TEXT_SELECTMODE>
{
    using Base = BobbyMenuDisplay;

public:
    SelectModeMenu();

    void start() override;
    void back() override;
};
