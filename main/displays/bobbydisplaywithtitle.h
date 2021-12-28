#pragma once

// system includes
#include <type_traits>

// 3rdparty lib includes
#include <displaywithtitle.h>

// local includes
#include "bobbydisplay.h"

class BobbyDisplayWithTitle : public espgui::DisplayWithTitle
{
    using Base = espgui::DisplayWithTitle;

public:
    void rawButtonPressed(uint8_t button) override;
    void rawButtonReleased(uint8_t button) override;

    void buttonPressed(espgui::Button button) override;
    void buttonReleased(espgui::Button button) override;
};
