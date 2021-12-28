#pragma once

// system includes
#include <type_traits>

// 3rdparty lib includes
#include <display.h>

enum BobbyButton
{
    Profile0 = espgui::Button::ButtonMax + 1,
    Profile1,
    Profile2,
    Profile3,
    Left2,
    Right2,
    Up2,
    Down2
};

class BobbyDisplay : public espgui::Display
{
    using Base = espgui::Display;

public:
    void rawButtonPressed(uint8_t button) override;
    void rawButtonReleased(uint8_t button) override;

    void buttonPressed(espgui::Button button) override;
    void buttonReleased(espgui::Button button) override;
};
