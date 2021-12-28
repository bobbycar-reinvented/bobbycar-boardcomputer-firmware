#pragma once

// system includes
#include <array>

// 3rdparty lib includes
#include <FastLED.h>

// local includes
#include "bobbydisplaywithtitle.h"
#include "ledstrip.h"

#ifdef FEATURE_LEDSTRIP
//extern int8_t selected_side;
//extern int8_t selected_color;
//extern bool state_select_color;
//extern bool last_state;

//extern const std::array<CRGB, 8> Colors;

//extern const std::array<uint16_t, 8> tft_colors;

class LedstripColorsDisplay : public BobbyDisplayWithTitle
{
    using Base = BobbyDisplayWithTitle;

public:
    std::string text() const override;
    void initScreen() override;
    void redraw() override;

    void buttonPressed(espgui::Button button) override;

    void drawColors();
    void drawSide(Bobbycar_Side side, unsigned int color);
    void clearSides();

private:
    bool already_drew_circle{false};
};
#endif
