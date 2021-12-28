#pragma once

// system includes
#include <type_traits>

// 3rdparty lib includes
#include <splitgraphdisplay.h>

// local includes
#include "bobbydisplay.h"

template<std::size_t COUNT0, std::size_t COUNT1>
class BobbySplitGraphDisplay : public espgui::SplitGraphDisplay<COUNT0, COUNT1>
{
    using Base = espgui::SplitGraphDisplay<COUNT0, COUNT1>;

public:
    void rawButtonPressed(uint8_t button) override;
    void rawButtonReleased(uint8_t button) override;

    void buttonPressed(espgui::Button button) override;
    void buttonReleased(espgui::Button button) override;
};
