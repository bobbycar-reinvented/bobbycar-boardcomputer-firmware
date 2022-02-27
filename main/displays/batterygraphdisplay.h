#pragma once

// 3rdparty lib includes

// local includes
#include "bobbydisplaywithtitle.h"

class BatteryGraphDisplay : public BobbyDisplayWithTitle {
    using Base = BobbyDisplayWithTitle;

public:
    std::string text() const override;
    void initScreen() override;
    void redraw() override;

    void buttonPressed(espgui::Button button) override;
};
