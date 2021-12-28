#pragma once

// system includes
#include <type_traits>

// 3rdparty lib includes
#include <graphdisplay.h>

// local includes
#include "bobbydisplay.h"

template<size_t COUNT>
class BobbyGraphDisplay : public espgui::GraphDisplay<COUNT>
{
    using Base = espgui::GraphDisplay<COUNT>;

public:
    void rawButtonPressed(uint8_t button) override;
    void rawButtonReleased(uint8_t button) override;

    void buttonPressed(espgui::Button button) override;
    void buttonReleased(espgui::Button button) override;
};
