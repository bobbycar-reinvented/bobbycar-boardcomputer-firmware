#pragma once

// 3rdparty lib includes
#include <tftinstance.h>
#include <widgets/label.h>
#include <widgets/progressbar.h>
#include <widgets/reverseprogressbar.h>

// local includes
#include "bobbydisplay.h"

class SpeedInfoDisplay : public BobbyDisplay
{
    using Base = BobbyDisplay;

public:
    void initScreen() override;
    void redraw() override;

    void buttonPressed(espgui::Button button) override;
private:
    espgui::Label m_labelSpeed{28, 70};

    espgui::ReverseProgressBar m_dischargingBar{10, 155, espgui::tft.width()/2 - 10, 25, 0, 40, TFT_GREEN};
    espgui::ProgressBar m_chargingBar{espgui::tft.width()/2, 155, espgui::tft.width()/2 - 10, 25, 0, 40, TFT_RED};
};
