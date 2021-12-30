#pragma once

// local includes
#include "displays/bobbymenudisplay.h"
#include "widgets/doubleprogressbar.h"

class BatteryMenu : public BobbyMenuDisplay
{
    using Base = BobbyMenuDisplay;

public:
    BatteryMenu();

    std::string text() const override;

    void start() override;
    void redraw() override;
    void back() override;

private:
    bobbygui::DoubleProgressBar m_doubleProgressBarBatPercentage{75, 68, 90, 24, 0, 100, TFT_RED, TFT_GREEN};
};
