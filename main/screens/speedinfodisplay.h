#pragma once

// 3rdparty lib includes
#include <delayedconstruction.h>
#include <tftinterface.h>
#include <widgets/label.h>
#include <widgets/variablerangeprogressbar.h>
#include <widgets/variablerangereverseprogressbar.h>

// local includes
#include "guihelpers/bobbydisplay.h"

namespace bobby {

class SpeedInfoDisplay : public BobbyDisplay
{
    using Base = BobbyDisplay;

public:
    void initScreen(espgui::TftInterface &tft) override;
    void redraw(espgui::TftInterface &tft) override;

    void buttonPressed(espgui::Button button) override;
private:
    espgui::Label m_labelSpeed{5, 5};

#define PROGRESS_BAR_START_Y 110
    cpputils::DelayedConstruction<espgui::VariableRangeReverseProgressBar> m_dischargingBar;
    cpputils::DelayedConstruction<espgui::VariableRangeProgressBar> m_chargingBar;

#define START_Y PROGRESS_BAR_START_Y + 28
#define LABEL_HEIGHT 27
    espgui::Label m_batteryPercentLabel{5, START_Y + LABEL_HEIGHT * 0};
    espgui::Label m_voltageLabel{5, START_Y + LABEL_HEIGHT * 1};
    espgui::Label m_distanceLabel{5, START_Y + LABEL_HEIGHT * 2};
    espgui::Label m_currentPowerLabel{5, START_Y + LABEL_HEIGHT * 3};
    espgui::Label m_performanceLabel{5, START_Y + LABEL_HEIGHT * 5};
};
} // namespace bobby
