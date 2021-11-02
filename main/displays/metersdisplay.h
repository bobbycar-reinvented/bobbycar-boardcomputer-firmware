#pragma once

// system includes
#include <array>

// 3rdparty lib includes
#include <display.h>
#include <actions/switchscreenaction.h>
#include <widgets/label.h>
#include <widgets/reverseprogressbar.h>
#include <widgets/progressbar.h>
#include <widgets/verticalmeter.h>
#include <widgets/vumeter.h>

class MetersDisplay :
    public espgui::Display
{
public:
    void initScreen() override;
    void redraw() override;

    void confirm() override;
    void back() override;
    void rotate(int offset) override;

private:
    espgui::VuMeter m_vuMeter;

    espgui::ReverseProgressBar m_dischargingBar{10, 135, 90, 15, 0, 40, TFT_GREEN};
    espgui::ProgressBar m_chargingBar{100, 135, 90, 15, 0, 40, TFT_RED};

    espgui::Label m_sumCurrentLabel{195,135};

    static constexpr auto x = 40;
    std::array<espgui::VerticalMeter, 6> meters{{
        espgui::VerticalMeter{"U f", "%.1f", 0*x, 160},
        espgui::VerticalMeter{"U b", "%.1f", 1*x, 160},
        espgui::VerticalMeter{"Ibl", "%.1f", 2*x, 160},
        espgui::VerticalMeter{"Ibr", "%.1f", 3*x, 160},
        espgui::VerticalMeter{"Ihl", "%.1f", 4*x, 160},
        espgui::VerticalMeter{"Ihr", "%.1f", 5*x, 160}
    }};
};
