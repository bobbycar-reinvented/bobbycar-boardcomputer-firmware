#pragma once

// system includes
#include <vector>

// 3rdparty lib includes
#include <FastLED.h>

// local includes
#include "bobbytypesafeenum.h"
#include "ledstripdefines.h"

#define OtaAnimationModesValues(x) \
    x(None) \
    x(GreenProgressBar) \
    x(ColorChangeAll)
DECLARE_BOBBYTYPESAFE_ENUM(OtaAnimationModes, : uint8_t, OtaAnimationModesValues)

#define LedstripAnimationValues(x) \
    x(DefaultRainbow) \
    x(Pride) \
    x(BetterRainbow) \
    x(SpeedSync) \
    x(CustomColor) \
    x(SnakeAnimation) \
    x(GasOMeter)
DECLARE_BOBBYTYPESAFE_ENUM(LedstripAnimation, : uint8_t, LedstripAnimationValues)

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
extern float gLedPosition; // yes, this is intendet as a float value! Do NOT change!

extern uint16_t blinkAnimation;

extern bool brakeLightsStatus;

void showDefaultLedstrip();
void showAnimation();
void showBetterRainbow();
void showSpeedSyncAnimation();
void showCustomColor();
void showSnakeAnimation();
void showGasOMeterAnimation();
void showOtaAnimation();
void showPrideAnimation();

void initLedStrip();
void updateLedStrip();

[[nodiscard]] bool activateAutomaticFrontLight();
