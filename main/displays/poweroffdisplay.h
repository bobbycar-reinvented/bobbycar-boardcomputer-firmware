#pragma once

// 3rdparty lib includes
#include <espchrono.h>

// local includes
#include "display.h"

class PoweroffDisplay : public espgui::Display
{
public:
    void start() override;
    void initScreen() override;
    void update() override;
    void redraw() override {}
    void stop() override;

    void confirm() override;
    void back() override;

private:
    espchrono::millis_clock::time_point m_startTime;
};
