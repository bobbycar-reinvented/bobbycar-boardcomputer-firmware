#pragma once

// local includes
#include "display.h"

#ifdef FEATURE_GARAGE
class GarageDisplay : public espgui::Display
{
public:
    void start() override;
    void initScreen() override;
    void redraw() override;
    void confirm() override;
    void back() override;

private:
};
#endif
