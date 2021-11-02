#pragma once

// system includes
#include <cstdint>

// local includes
#include "display.h"
#include "actions/switchscreenaction.h"

class SpiroDisplay : public espgui::Display
{
    using Base = espgui::Display;

public:
    void initScreen() override;
    void redraw() override;
    void stop() override;

    void confirm() override;
    void back() override;

private:
    constexpr static auto DEG2RAD = 0.0174532925;

    static unsigned int rainbow(int value);

    float sx = 0, sy = 0;
    uint16_t x0 = 0, x1 = 0, yy0 = 0, yy1 = 0;

    long i{0};
    int n{}, r{}, colour{};
};
