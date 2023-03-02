#pragma once

// system includes
#ifdef LEDSTRIP_USE_ARRAY
#include <array>
#else
#include <vector>
#endif
#include <cstdint>

// 3rdparty lib includes
#include <espchrono.h>
#include <FastLED.h>

namespace bobby::ledstrip {

enum Bobbycar_Side
{
    FRONT_RIGHT,
    RIGHT,
    BACK_RIGHT,
    BACK,
    BACK_LEFT,
    LEFT,
    FRONT_LEFT,
    FRONT
};

#ifndef LEDSTRIP_USE_ARRAY
extern std::vector<CRGB> leds;
#else
extern std::array<CRGB, LEDSTRIP_USE_ARRAY> leds;
#endif

extern uint8_t gHue;
extern float gLedPosition; // yes, this is intendet as a float value! Do NOT change!

extern uint16_t blinkAnimation;

extern bool brakeLightsStatus;

extern espchrono::millis_clock::time_point brakeLightTimer;

void showDefaultLedstrip();

void showAnimation();

void showBetterRainbow();

void showSpeedSyncAnimation();

void showCustomColor();

void showSnakeAnimation();

void showGasOMeterAnimation();

void showOtaAnimation();

void showPrideAnimation();

void showWarningAnimation();

void showDrehlichtAnimation();

void showMancheLKWShabensoeinelichtanimation();

void initLedStrip();

void updateLedStrip();

[[nodiscard]] bool activateAutomaticFrontLight();

} // namespace bobby::ledstrip
