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

    static constexpr auto x = 40;
    std::array<VerticalMeter, 6> meters{{
        VerticalMeter{"U f", 0*x, 160},
        VerticalMeter{"U b", 1*x, 160},
        VerticalMeter{"Ivl", 2*x, 160},
        VerticalMeter{"Ivr", 3*x, 160},
        VerticalMeter{"Ihl", 4*x, 160},
        VerticalMeter{"Ihr", 5*x, 160}
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

    meters[0].redraw(fixBatVoltage(controllers.front.feedback.batVoltage), 35, 50);
    meters[1].redraw(fixBatVoltage(controllers.back.feedback.batVoltage), 35, 50);
    meters[2].redraw(fixCurrent(controllers.front.feedback.left.current), -10, 10);
    meters[3].redraw(fixCurrent(controllers.front.feedback.right.current), -10, 10);
    meters[4].redraw(fixCurrent(controllers.back.feedback.left.current), -10, 10);
    meters[5].redraw(fixCurrent(controllers.back.feedback.right.current), -10, 10);
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
