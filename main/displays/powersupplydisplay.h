#pragma once

// 3rdparty lib includes
#include "display.h"
#include "widgets/label.h"

#if defined(FEATURE_CAN) && defined(FEATURE_POWERSUPPLY)
class PowerSupplyDisplay : public espgui::Display
{
    using Base = espgui::Display;

public:
    void initScreen() override;
    void redraw() override;

    void confirm() override;
    void back() override;

    void rotate(int offset) override;

    espgui::Label m_voltageLabel{120, 50};
    espgui::Label m_currentLabel{120, 75};
};
#endif
