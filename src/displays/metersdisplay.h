#pragma once

#include <array>

#include <Arduino.h>

#include "display.h"
#include "actions/switchscreenaction.h"
#include "globals.h"
#include "utils.h"
#include "widgets/verticalmeter.h"
#include "widgets/vumeter.h"

namespace {
class MainMenu;
class StatusDisplay;
class BmsDisplay;
}

namespace {
class MetersDisplay : public Display, public ConfirmActionInterface<SwitchScreenAction<MainMenu>>, public BackActionInterface<SwitchScreenAction<MainMenu>>
{
public:
    void initScreen() override;
    void redraw() override;

    void rotate(int offset) override;

private:
    VuMeter m_vuMeter;

    int d = 0;

    static constexpr auto x = 40;
    std::array<VerticalMeter, 6> meters{{
        VerticalMeter{"A0", 0*x, 160},
        VerticalMeter{"A1", 1*x, 160},
        VerticalMeter{"A2", 2*x, 160},
        VerticalMeter{"A3", 3*x, 160},
        VerticalMeter{"A4", 4*x, 160},
        VerticalMeter{"A5", 5*x, 160}
    }};
};

void MetersDisplay::initScreen()
{
    tft.fillScreen(TFT_BLACK);

    m_vuMeter.start();

    for (auto &meter : meters)
        meter.start();
}

void MetersDisplay::redraw()
{
    m_vuMeter.redraw(avgSpeedKmh);

    int i{};
    for (auto &meter : meters)
        meter.redraw(50 + 50 * sin((d + (i++ * 60)) * 0.0174532925));

    d += 4; if (d >= 360) d -= 360;
}

void MetersDisplay::rotate(int offset)
{
    if (offset < 0)
        switchScreen<StatusDisplay>();
    else if (offset > 0)
#ifdef FEATURE_BMS
        switchScreen<BmsDisplay>();
#else
        switchScreen<StatusDisplay>();
#endif
}
}
