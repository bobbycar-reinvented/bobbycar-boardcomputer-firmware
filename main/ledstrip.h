#pragma once
#ifdef FEATURE_LEDSTRIP
// 3rdparty lib includes
#include <FastLED.h>

// local includes
#include "globals.h"
#include "cpputils.h"
#include "espchrono.h"
#include "ledstripdefines.h"

namespace {
std::vector<CRGB> leds;
uint8_t gHue = 0;

int16_t blinkAnimation = LEDSTRIP_OVERWRITE_NONE;
int16_t animation_type = LEDSTRIP_ANIMATION_TYPE_DEFAULTRAINBOW;

void showDefaultLedstrip();
void showAnimation();
void showBetterRainbow();
void showSpeedSyncAnimation();

void initLedStrip()
{
    animation_type = settings.ledstrip.animationType;
    leds.resize(settings.ledstrip.ledsCount);
    FastLED.addLeds<NEOPIXEL, PINS_LEDSTRIP>(&*std::begin(leds), leds.size())
        .setCorrection(TypicalSMD5050);
}

void updateLedStrip()
{
    EVERY_N_MILLISECONDS( 20 ) { gHue++; }
    static bool have_disabled_beeper = false;

    if (cpputils::is_in(blinkAnimation, LEDSTRIP_OVERWRITE_BLINKLEFT, LEDSTRIP_OVERWRITE_BLINKRIGHT, LEDSTRIP_OVERWRITE_BLINKBOTH))
    {
        std::fill(std::begin(leds), std::end(leds), CRGB{0, 0, 0});
        if (espchrono::millis_clock::now().time_since_epoch() % 750ms < 375ms)
        {
            if (settings.ledstrip.enableBeepWhenBlink)
            {
                for (Controller &controller : controllers)
                    controller.command.buzzer.freq = 3;
            }
            auto color = CRGB{255, 255, 0};
            const auto center = (std::begin(leds) + (leds.size() / 2) + settings.ledstrip.centerOffset);

            if (blinkAnimation != LEDSTRIP_OVERWRITE_BLINKRIGHT && !settings.ledstrip.enableFullBlink)
            {
                std::fill(center - settings.ledstrip.bigOffset, center - settings.ledstrip.smallOffset, color);
            }
            else if(blinkAnimation != LEDSTRIP_OVERWRITE_BLINKRIGHT && settings.ledstrip.enableFullBlink)
            {
                std::fill(std::begin(leds), center, color);
            }
            if (blinkAnimation != LEDSTRIP_OVERWRITE_BLINKLEFT && !settings.ledstrip.enableFullBlink)
            {
                std::fill(center + settings.ledstrip.smallOffset, center + settings.ledstrip.bigOffset, color);
            }
            else if(blinkAnimation != LEDSTRIP_OVERWRITE_BLINKLEFT && settings.ledstrip.enableFullBlink)
            {
                std::fill(center, std::end(leds), color);
            }

        } else {
            if (settings.ledstrip.enableBeepWhenBlink)
            {
                for (Controller &controller : controllers)
                    controller.command.buzzer.freq = 0;
            }
        }
    }
    else
    {
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

                const auto center = (std::begin(leds) + (leds.size() / 2) + settings.ledstrip.centerOffset);

                std::fill(std::begin(leds), std::end(leds), CRGB{0, 0, 0});
                if (settings.ledstrip.enableFullBlink)
                {
                    std::fill(std::begin(leds), std::end(leds), color);
                }
                else
                {
                    std::fill(center - settings.ledstrip.bigOffset, center - settings.ledstrip.smallOffset, color);
                    std::fill(center + settings.ledstrip.smallOffset, center + settings.ledstrip.bigOffset, color);
                }
            }
            else
            {
                showAnimation();
            }
        }
        else
        {
            showAnimation();
        }
    }

    if (have_disabled_beeper == false && (!(cpputils::is_in(blinkAnimation, LEDSTRIP_OVERWRITE_BLINKLEFT, LEDSTRIP_OVERWRITE_BLINKRIGHT, LEDSTRIP_OVERWRITE_BLINKBOTH)) || !settings.ledstrip.enableBeepWhenBlink))
    {
        for (Controller &controller : controllers)
            controller.command.buzzer.freq = 0;
        have_disabled_beeper = true;
    }
    else if ((cpputils::is_in(blinkAnimation, LEDSTRIP_OVERWRITE_BLINKLEFT, LEDSTRIP_OVERWRITE_BLINKRIGHT, LEDSTRIP_OVERWRITE_BLINKBOTH)) && settings.ledstrip.enableBeepWhenBlink) have_disabled_beeper = false;

    FastLED.setMaxPowerInVoltsAndMilliamps(5,settings.ledstrip.deziampere * 100);
    FastLED.show();
}

void showAnimation() {
    if (animation_type == LEDSTRIP_ANIMATION_TYPE_DEFAULTRAINBOW) showDefaultLedstrip();
    else if (animation_type == LEDSTRIP_ANIMATION_TYPE_BETTERRAINBOW) showBetterRainbow();
    else if (animation_type == LEDSTRIP_ANIMATION_TYPE_SPEEDSYNCANIMATION) showSpeedSyncAnimation();
    else showDefaultLedstrip();
}

void showBetterRainbow() {
    if (settings.ledstrip.enableLedAnimation)
    {
        fill_rainbow(&*std::begin(leds), leds.size(), gHue);
    }
    else
        std::fill(std::begin(leds), std::end(leds), CRGB{0, 0, 0});
}

void fill_rainbow_invert_at( struct CRGB * pFirstLED, int numToFill, int invertAtLed,
                  uint8_t initialhue,
                  float deltahue )
{
    float huecalc = initialhue;
    CHSV hsv;
    hsv.hue = initialhue;
    hsv.val = 255;
    hsv.sat = 240;
    for( int i = 0; i < numToFill; i++) {
        hsv.hue = huecalc;
        pFirstLED[i] = hsv;
        if(i>invertAtLed){
            huecalc -= deltahue;
        }else{
            huecalc += deltahue;
        }
    }
}

void showSpeedSyncAnimation() {
    if (settings.ledstrip.enableLedAnimation)
    {
#ifdef LEDS_PER_METER
        const float leds_per_meter = LEDS_PER_METER;
#else
        const float leds_per_meter = 144;
#endif

        static auto last_interval = espchrono::millis_clock::now();
        auto difference_ms = espchrono::ago(last_interval).count();

        static float hue_result = 0;

        const float hue_per_led = .1;
        const float meter_per_second = avgSpeedKmh / 3.6;
        const float leds_per_second = meter_per_second * leds_per_meter;
        const float hue_per_second = leds_per_second * hue_per_led;

        hue_result += hue_per_second * difference_ms / 1000.f;

        fill_rainbow_invert_at(&*std::begin(leds), leds.size(),leds.size()/2, hue_result,-hue_per_led);

        last_interval = espchrono::millis_clock::now();
    }
    else
        std::fill(std::begin(leds), std::end(leds), CRGB{0, 0, 0});
}

void showDefaultLedstrip()
{
    if (settings.ledstrip.enableLedAnimation)
    {
        fadeToBlackBy(&*std::begin(leds), leds.size(), 20);

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
