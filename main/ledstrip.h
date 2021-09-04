#pragma once

#ifdef FEATURE_LEDSTRIP
// 3rdparty lib includes
#include <FastLED.h>

// local includes
#include "globals.h"

namespace {
bool enableLedAnimation{false};

std::array<CRGB, LEDSTRIP_LENGTH> leds;
uint8_t gHue = 0;

void showDefaultLedstrip();

void initLedStrip()
{
    FastLED.addLeds<NEOPIXEL, PINS_LEDSTRIP>(std::begin(leds), leds.size())
        .setCorrection(TypicalSMD5050);
}

void updateLedStrip()
{
    EVERY_N_MILLISECONDS( 20 ) { gHue++; }

    if (settings.ledstrip.enableBrakeLights)
    {
        float avgPwm{};
        for (const Controller &controller : controllers)
        {
            avgPwm +=
                controller.command.left.pwm * (controller.invertLeft ? -1 : 1) +
                controller.command.right.pwm * (controller.invertRight ? -1 : 1);
        }
        avgPwm /= 4;

        if (avgPwm < -1.f)
        {
            auto color = avgSpeedKmh < -0.1f ? CRGB{255, 255, 255} : CRGB{255, 0, 0};
            constexpr auto kleinerOffset = 4;
            constexpr auto grosserOffset = 10;

            const auto center = std::begin(leds) + (leds.size() / 2) + 1;

            std::fill(std::begin(leds), std::end(leds), CRGB{0, 0, 0});
            std::fill(center - grosserOffset, center - kleinerOffset, color);
            std::fill(center + kleinerOffset, center + grosserOffset, color);
        }
        else
        {
            showDefaultLedstrip();
        }
    }
    else
    {
        showDefaultLedstrip();
    }

    FastLED.show();
}

void showDefaultLedstrip()
{
    if (enableLedAnimation)
    {
        fadeToBlackBy(std::begin(leds), leds.size(), 20);

        uint8_t dothue = 0;
        for (int i = 0; i < 8; i++)
        {
            leds[beatsin16(i + 7, 0, leds.size())] |= CHSV(dothue, 200, 255);
            dothue += 32;
        }
    }
    else
        std::fill(std::begin(leds), std::end(leds), CRGB{0, 0, 0});
}
} // namespace
#endif
