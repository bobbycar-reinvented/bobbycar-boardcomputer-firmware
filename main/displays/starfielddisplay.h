#pragma once

// system includes
#include <cstdint>

// local includes
#include "display.h"

class StarfieldDisplay : public espgui::Display
{
public:
    StarfieldDisplay();

    void confirm() override;
    void back() override;

    void initScreen() override;
    void redraw() override;
    void stop() override;

private:
    static constexpr auto NSTARS = 1024;

    uint8_t sx[NSTARS] = {};
    uint8_t sy[NSTARS] = {};
    uint8_t sz[NSTARS] = {};

    uint8_t za, zb, zc, zx;
};
