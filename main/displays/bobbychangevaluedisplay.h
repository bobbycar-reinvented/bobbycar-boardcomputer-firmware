#pragma once

// system includes
#include <type_traits>

// 3rdparty lib includes
#include <changevaluedisplay.h>

// local includes
#include "bobbydisplay.h"

template<typename Tvalue>
class BobbyChangeValueDisplay : public espgui::ChangeValueDisplay<Tvalue>
{
    using Base = espgui::ChangeValueDisplay<Tvalue>;

public:
    void rawButtonPressed(uint8_t button) override;
    void rawButtonReleased(uint8_t button) override;

    void buttonPressed(espgui::Button button) override;
    void buttonReleased(espgui::Button button) override;
};
