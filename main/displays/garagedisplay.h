#pragma once

// local includes
#include "bobbydisplay.h"

#ifdef FEATURE_GARAGE
class GarageDisplay : public BobbyDisplay
{
    using Base = BobbyDisplay;

public:
    void start() override;
    void initScreen() override;
    void redraw() override;

    void buttonPressed(espgui::Button button) override;

private:
};
#endif
