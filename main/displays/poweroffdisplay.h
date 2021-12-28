#pragma once

// 3rdparty lib includes
#include <espchrono.h>

// local includes
#include "bobbydisplay.h"

class PoweroffDisplay : public BobbyDisplay
{
    using Base = BobbyDisplay;

public:
    void start() override;
    void initScreen() override;
    void update() override;
    void stop() override;

private:
    espchrono::millis_clock::time_point m_startTime;
};
