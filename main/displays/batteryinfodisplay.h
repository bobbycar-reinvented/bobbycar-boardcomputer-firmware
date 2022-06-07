#pragma once

// local includes
#include "bobbydisplay.h"

class BatteryInfoDisplay : public BobbyDisplay
{
    using Base = BobbyDisplay;

public:
    void initScreen() override;
    void redraw() override;

    void buttonPressed(espgui::Button button) override;
private:
    static constexpr const auto m_offset = 40;
    uint16_t m_lastBarCount{0};
};
