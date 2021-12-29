#pragma once

// 3rdparty lib includes
#include <popupdisplay.h>

class BobbyPopupDisplay : public espgui::PopupDisplay
{
    using Base = espgui::PopupDisplay;

public:
    using Base::Base;

    void rawButtonPressed(uint8_t button) override;
    void rawButtonReleased(uint8_t button) override;

    void buttonPressed(espgui::Button button) override;
    void buttonReleased(espgui::Button button) override;
};
