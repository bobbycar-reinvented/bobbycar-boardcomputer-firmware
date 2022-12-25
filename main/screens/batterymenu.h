#pragma once

// 3rdparty lib includes
#include <tftcolors.h>
#include <tftinterface.h>
#include <widgets/doubleprogressbar.h>
#include <widgets/label.h>

// local includes
#include "guihelpers/bobbymenudisplay.h"

namespace bobby {

class BatteryMenu : public BobbyMenuDisplay
{
    using Base = BobbyMenuDisplay;

public:
    BatteryMenu();

    std::string text() const override;

    void initScreen(espgui::TftInterface &tft) override;
    void redraw(espgui::TftInterface &tft) override;
    void back() override;

private:
    bobby::DoubleProgressBar m_doubleProgressBarBatPercentage{75, 68, 90, 24, 0, 100, espgui::TFT_RED, espgui::TFT_GREEN};
    espgui::Label m_batPercentNowLabel {170, 68};
    espgui::Label m_batPercentBootLabel{170, 82};
};

} // namespace bobby
