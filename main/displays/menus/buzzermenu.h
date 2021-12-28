#pragma once

// local includes
#include "displays/bobbymenudisplay.h"
#include "texts.h"

class BuzzerMenu :
    public BobbyMenuDisplay,
    public espgui::StaticText<TEXT_BUZZER>
{
public:
    BuzzerMenu();

    void back() override;
};
