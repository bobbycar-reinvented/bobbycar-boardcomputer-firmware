#pragma once

// local includes
#include "bobbydisplay.h"

class SpeedInfoDisplay : public BobbyDisplay
{
    using Base = BobbyDisplay;

public:
    void initScreen() override;
    void redraw() override;

    void buttonPressed(espgui::Button button) override;
};
