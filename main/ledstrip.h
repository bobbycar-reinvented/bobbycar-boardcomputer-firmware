#pragma once

// system includes
#include <vector>

// 3rdparty lib includes
#include <FastLED.h>

#ifdef FEATURE_LEDSTRIP
#define crgb_iterator __gnu_cxx::__normal_iterator<CRGB *, std::vector<CRGB>>
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

extern std::vector<CRGB> leds;
extern uint8_t gHue;

extern int16_t blinkAnimation;
extern int16_t animation_type;

void showDefaultLedstrip();
void showAnimation();
void showBetterRainbow();
void showSpeedSyncAnimation();
void showCustomColor();

void initLedStrip();
void updateLedStrip();
#endif
