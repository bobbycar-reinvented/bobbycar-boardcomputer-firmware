#include "ledstrip.h"

// system includes
#include <cmath>

// 3rdparty lib includes
#include <cpputils.h>
#include <espchrono.h>
#include <recursivelockhelper.h>

// local includes
#include "enums.h"
#include "globallock.h"
#include "globals.h"
#include "ledstripdefines.h"
#include "newsettings.h"
#include "ota.h"
#include "time_bobbycar.h"
#include "utils.h"

using namespace std::chrono_literals;

namespace bobby::ledstrip {

std::vector<CRGB> leds;
uint8_t gHue = 0;
float gLedPosition = 0; // yes, this is intendet as a float value! Do NOT change!

bool brakeLightsStatus;

espchrono::millis_clock::time_point brakeLightTimer;

uint16_t blinkAnimation = LEDSTRIP_OVERWRITE_NONE;

namespace {
bool initialized{false};

bool brakeLights()
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
        return true;
    }

    if (configs.ledstrip.brakeLights_useAccel.value() && (avgAccel < -0.001f && avgSpeedKmh > 2.f))
    {
        return true;
    }

    if (espchrono::ago(brakeLightTimer) < 200ms)
    {
        return true;
    }

    if (configs.ledstrip.brakeLights_usePower.value() && brakeLightsStatus)
    {
        if (const auto avgVoltage = controllers.getAvgVoltage(); avgVoltage)
        {
            const auto watt = sumCurrent * *avgVoltage;

            return watt < -1;
        }
    }

    return false;
}
} // namespace

void initLedStrip()
{
    //return;
    if (configs.feature.ledstrip.isEnabled.value())
    {
        leds.resize(configs.ledstrip.ledsCount.value());
        FastLED.addLeds<NEOPIXEL, PINS_LEDSTRIP>(&*std::begin(leds), leds.size())
            .setCorrection(TypicalSMD5050);
        initialized = true;
    }
}

void updateLedStrip()
{
#ifdef OTA_FIX
    if (ota::isOtaInProgress())
        return;
#endif
    if (configs.feature.ledstrip.isEnabled.value() && !initialized)
    {
        initLedStrip();
        return;
    }

    espcpputils::RecursiveLockHelper helper{global_lock->handle};

    if (!helper.locked())
    {
        ESP_LOGE("LED", "Failed to lock global lock");
        return;
    }

    if (!configs.feature.ledstrip.isEnabled.value() && initialized)
    {
        std::fill(std::begin(leds), std::end(leds), CRGB::Black);
        FastLED.show();
        initialized = false;
        return;
    }
    else if (!configs.feature.ledstrip.isEnabled.value())
        return;

    // enter if
    if (espchrono::millis_clock::now().time_since_epoch() < 5s)
    {
        std::fill(std::begin(leds), std::end(leds), simplified ? CRGB::Gold : CRGB::Green);
        return;
    }

    EVERY_N_MILLISECONDS( 20 ) { gHue++; }
    static bool have_disabled_beeper = false;
    const bool enAnim = configs.ledstrip.enableAnimBlink.value();

    if (cpputils::is_in(blinkAnimation, LEDSTRIP_OVERWRITE_BLINKLEFT, LEDSTRIP_OVERWRITE_BLINKRIGHT, LEDSTRIP_OVERWRITE_BLINKBOTH))
    {
        std::fill(std::begin(leds), std::end(leds), CRGB{0, 0, 0});
        if (espchrono::utc_clock::now().time_since_epoch() % 750ms < 375ms || enAnim)
        {
            const auto anim_to_fill = time_to_percent(
                    750ms,
                    500ms,
                    100ms,
                    configs.ledstrip.enableFullBlink.value() ?
                        (leds.size() % 2 == 0 ? leds.size() / 2 : leds.size() / 2 - 1) :
                        configs.ledstrip.bigOffset.value() - configs.ledstrip.smallOffset.value(),
                    configs.ledstrip.enableFullBlink.value()
            );
            if (configs.ledstrip.enableBeepWhenBlink.value())
            {
                if (espchrono::utc_clock::now().time_since_epoch() % 750ms < 375ms)
                    for (Controller &controller : controllers)
                        controller.command.buzzer.freq = 3;
                else
                    for (Controller &controller : controllers)
                        controller.command.buzzer.freq = 0;
            }
            auto color = CRGB{255, 200, 0};
            const auto center = (std::begin(leds) + (leds.size() / 2) + configs.ledstrip.centerOffset.value());

            if (configs.ledstrip.enableFullBlink.value())
            {
                // Full
                if (BLINK_LEFT_EXPR)
                {
                    // Blink left
                    if (!enAnim)
                    {
                        std::fill(std::begin(leds), center, color);
                    }
                    else
                    {
                        std::fill(std::begin(leds) + anim_to_fill, center, color);
                    }
                }
                if (BLINK_RIGHT_EXPR)
                {
                    // Blink right
                    if (!enAnim)
                    {
                        std::fill(center, std::end(leds), color);
                    }
                    else
                    {
                        std::fill(center, std::end(leds) - anim_to_fill, color);
                    }
                }
            }
            else
            {
                // Only in the back
                if (BLINK_LEFT_EXPR)
                {
                    // Blink left
                    if (!enAnim)
                    {
                        std::fill(center - configs.ledstrip.bigOffset.value(), center - configs.ledstrip.smallOffset.value(), color);
                    }
                    else
                    {
                        std::fill(center - configs.ledstrip.smallOffset.value() - anim_to_fill, center - configs.ledstrip.smallOffset.value(), color);
                    }
                }
                if (BLINK_RIGHT_EXPR)
                {
                    // Blink right
                    if (!enAnim)
                    {
                        std::fill(center + configs.ledstrip.smallOffset.value(), center + configs.ledstrip.bigOffset.value(), color);
                    }
                    else
                    {
                        std::fill(center + configs.ledstrip.smallOffset.value(), center + configs.ledstrip.smallOffset.value() + anim_to_fill, color);
                    }
                }
            }
        } else {
            if (configs.ledstrip.enableBeepWhenBlink.value())
            {
                for (Controller &controller : controllers)
                    controller.command.buzzer.freq = 0;
            }
        }
    }
    else
    {
        if (configs.ledstrip.enableBrakeLights.value())
        {
            // avgAccel in m/s/s
            if (brakeLights())
            {
                if (!(espchrono::ago(brakeLightTimer) < 200ms))
                {
                    brakeLightTimer = espchrono::millis_clock::now();
                }

                auto color = avgSpeedKmh < -0.1f ? CRGB{255, 255, 255} : CRGB{255, 0, 0};

                brakeLightsStatus = true;

                std::fill(std::begin(leds), std::end(leds), CRGB{0, 0, 0});
                if (configs.ledstrip.enableFullBlink.value())
                {
                    std::fill(std::begin(leds), std::end(leds), color);
                }
                else if(!configs.ledstrip.enableAnimBlink.value())
                {
                    const auto center = (std::begin(leds) + (leds.size() / 2) + configs.ledstrip.centerOffset.value());

                    std::fill(center - configs.ledstrip.bigOffset.value() - 2, center - configs.ledstrip.smallOffset.value() + 2, color);
                    std::fill(center + configs.ledstrip.smallOffset.value() - 2, center + configs.ledstrip.bigOffset.value() + 2, color);
                }
            }
            else
            {
                brakeLightsStatus = false;
                showAnimation();
            }
        }
        else
        {
            showAnimation();
        }
    }

    if (!have_disabled_beeper && (!(cpputils::is_in(blinkAnimation, LEDSTRIP_OVERWRITE_BLINKLEFT, LEDSTRIP_OVERWRITE_BLINKRIGHT, LEDSTRIP_OVERWRITE_BLINKBOTH)) || !configs.ledstrip.enableBeepWhenBlink.value()))
    {
        for (Controller &controller : controllers)
            controller.command.buzzer.freq = 0;
        have_disabled_beeper = true;
    }
    else if ((cpputils::is_in(blinkAnimation, LEDSTRIP_OVERWRITE_BLINKLEFT, LEDSTRIP_OVERWRITE_BLINKRIGHT, LEDSTRIP_OVERWRITE_BLINKBOTH)) && configs.ledstrip.enableBeepWhenBlink.value()) have_disabled_beeper = false;

    const auto automaticLight = activateAutomaticFrontLight();

    if (simplified || configs.ledstrip.enableStVO.value() || automaticLight)
    {
       const auto center = (std::begin(leds) + (leds.size() / 2) + configs.ledstrip.centerOffset.value());

       if (!(blinkAnimation == LEDSTRIP_OVERWRITE_BLINKLEFT || blinkAnimation == LEDSTRIP_OVERWRITE_BLINKBOTH) || !(espchrono::utc_clock::now().time_since_epoch() % 750ms < 375ms) || configs.ledstrip.enableFullBlink.value()) // Condition for right
       {
           std::fill(center - configs.ledstrip.bigOffset.value(), center - configs.ledstrip.smallOffset.value(), CRGB{0, 0, 0});
           std::fill(center - configs.ledstrip.bigOffset.value() - 1U, center - configs.ledstrip.smallOffset.value() - 1U, CRGB{255, 0, 0}); // Right
       }
       if (!(blinkAnimation == LEDSTRIP_OVERWRITE_BLINKRIGHT || blinkAnimation == LEDSTRIP_OVERWRITE_BLINKBOTH) || !(espchrono::utc_clock::now().time_since_epoch() % 750ms < 375ms) || configs.ledstrip.enableFullBlink.value()) // Condition for left
       {
           std::fill(center + configs.ledstrip.smallOffset.value(), center + configs.ledstrip.bigOffset.value(), CRGB{0, 0, 0});
           std::fill(center + configs.ledstrip.smallOffset.value() + 1U, center + configs.ledstrip.bigOffset.value() + 1U, CRGB{255, 0, 0}); // Left
       }

       if (configs.ledstrip.stvoFrontEnable.value() || automaticLight)
       {
       std::fill(std::begin(leds) + configs.ledstrip.stvoFrontOffset.value(), std::begin(leds) + configs.ledstrip.stvoFrontOffset.value() + configs.ledstrip.stvoFrontLength.value(), CRGB{255, 255, 255});
       std::fill(std::end(leds) - configs.ledstrip.stvoFrontOffset.value() - configs.ledstrip.stvoFrontLength.value(), std::end(leds) - configs.ledstrip.stvoFrontOffset.value(), CRGB{255, 255, 255});
       }
    }

    FastLED.setMaxPowerInVoltsAndMilliamps(5, configs.ledstrip.maxMilliamps.value());
    FastLED.setBrightness(configs.ledstrip.brightness.value());
    FastLED.show();
}

void showAnimation()
{
    if (configs.ledstrip.enableLedAnimation.value()
        && !(ota::isOtaInProgress() && configs.ledstrip.otaMode.value() != OtaAnimationModes::None)
        )
    {
        switch (configs.ledstrip.animationType.value())
        {
        case LedstripAnimation::DefaultRainbow: showDefaultLedstrip(); break;
        case LedstripAnimation::BetterRainbow: showBetterRainbow(); break;
        case LedstripAnimation::SpeedSync: showSpeedSyncAnimation(); break;
        case LedstripAnimation::CustomColor: showCustomColor(); break;
        case LedstripAnimation::SnakeAnimation: showSnakeAnimation(); break;
        case LedstripAnimation::GasOMeter: showGasOMeterAnimation(); break;
        case LedstripAnimation::Pride: showPrideAnimation(); break;
        case LedstripAnimation::WarningAnimation: showWarningAnimation(); break;
        case LedstripAnimation::Drehlicht: showDrehlichtAnimation(); break;
        case LedstripAnimation::MancheLKWsHabenDieseAnimation: showMancheLKWShabensoeinelichtanimation(); break;
        default: showDefaultLedstrip();
        }
    }
    else if (ota::isOtaInProgress() && configs.ledstrip.otaMode.value() != OtaAnimationModes::None)
    {
        // show ota animation
        showOtaAnimation();
    }

    fadeToBlackBy(leds.data(), leds.size(), 35);
}

void showOtaAnimation()
{
    std::fill(std::begin(leds), std::end(leds), CRGB{0,0,0});
    const auto leds_count = leds.size();

    //const auto progress = ota::otaProgress();
    if (const auto totalSize = ota::otaTotalSize(); totalSize && *totalSize > 0)
    {
        const float percentage = ota::otaPercent();
        if (configs.ledstrip.otaMode.value() == OtaAnimationModes::GreenProgressBar)
        {
            int numLeds = (leds_count * percentage) / 100;
            if (numLeds >= leds_count)
            {
                numLeds = leds_count - 1;
            }
            std::fill(std::begin(leds), std::begin(leds) + numLeds, CRGB{0,255,0});
        }
        else if (configs.ledstrip.otaMode.value() == OtaAnimationModes::ColorChangeAll)
        {
            const uint8_t redChannel = 255 - (2.55f * percentage);
            const uint8_t greenChannel = 2.55f * percentage;

            std::fill(std::begin(leds), std::end(leds), CRGB{redChannel, greenChannel, 0});
        }
    }
}

void showBetterRainbow()
{
    fill_rainbow(&*std::begin(leds), leds.size(), gHue);
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
    for (int i = 0; i < numToFill; i++) {
        hsv.hue = huecalc;
        pFirstLED[i] = hsv;
        if (i>invertAtLed)
        {
            huecalc -= deltahue;
        }
        else
        {
            huecalc += deltahue;
        }
    }
}

void showSpeedSyncAnimation()
{
    static auto last_interval = espchrono::millis_clock::now();
    const auto difference_ms = espchrono::ago(last_interval) / 1ms;

    static float hue_result = 0;

    const float hue_per_led = 1.f / std::max(uint8_t(1), uint8_t(configs.ledstrip.animationMultiplier.value()));
    const float meter_per_second = avgSpeedKmh / 3.6f;
    const float leds_per_second = meter_per_second * configs.ledstrip.leds_per_meter.value();
    const float hue_per_second = leds_per_second * hue_per_led;

    hue_result += hue_per_second * difference_ms / 1000.f;

    fill_rainbow_invert_at(&*std::begin(leds), leds.size(),leds.size()/2, hue_result,-hue_per_led);

    last_interval = espchrono::millis_clock::now();
}

void showDefaultLedstrip()
{
    fadeToBlackBy(&*std::begin(leds), leds.size(), 20);

    uint8_t dothue = 0;
    for (int i = 0; i < 8; i++)
    {
        leds[beatsin16(i + 7, 0, leds.size())] |= CHSV(dothue, 200, 255);
        dothue += 32;
    }
}

void showSnakeAnimation()
{
    const float leds_per_cycle = (1.f / std::max<int16_t>(1, configs.ledstrip.animationMultiplier.value())) * (avgSpeedKmh + 1); // yes, this is intended as a float value! Do NOT change!
    fadeToBlackBy(&*std::begin(leds), leds.size(), floor(20*leds_per_cycle));
    if (gLedPosition >= leds.size())
    {
        gLedPosition = 0;
    }

    if (gHue == 255) {
        gHue = 0;
    }

    for(int16_t i = floor(gLedPosition); i < floor(gLedPosition + leds_per_cycle); i++)
    {
        leds[i] |= CHSV(gHue, 255, 255);
        uint8_t snake_2_pos = floorf(leds.size() / 2.f) + i;

        if (snake_2_pos > leds.size())
        {
            snake_2_pos -= leds.size();
        }
        leds[snake_2_pos] |= CHSV(gHue, 255, 255);
    }

    gLedPosition += leds_per_cycle;
    gHue += 5;
}

void showGasOMeterAnimation()
{
    if (const auto avgVoltage = controllers.getAvgVoltage(); avgVoltage)
    {
        auto watt = sumCurrent * *avgVoltage;
        auto w_per_kmh = watt / std::abs(avgSpeedKmh);
        CRGB color = 0;
        if (std::isinf(w_per_kmh) || std::isnan(w_per_kmh))
        {
            color = 0;
        }
        else if (w_per_kmh <= -40)
        {
            color = CRGB(255, 0, 255);
        }
        else if (w_per_kmh < -20)
        {
            color = CRGB(255, 0, cpputils::mapValueClamped<float>(w_per_kmh, -40, -20, 255.f, 0.f));
        }
        else if (w_per_kmh < 0)
        {
            color = CRGB(255, cpputils::mapValueClamped<float>(w_per_kmh, -20, 0, 0.f, 255.f), 0);
        }
        else if (w_per_kmh < 20)
        {
            color = CRGB(cpputils::mapValueClamped<float>(w_per_kmh, 0, 20, 255.f, 0.f), 255, 0);
        }
        else if (w_per_kmh < 40)
        {
            color = CRGB(0, cpputils::mapValueClamped<float>(w_per_kmh, 20, 40, 255.f, 0.f), cpputils::mapValueClamped<float>(w_per_kmh, 20, 40, 0.f, 255.f));
        }
        else
        {
            color = CRGB(0, 0, 255);
        }
        std::fill(std::begin(leds), std::end(leds), color);
    }
}

void showCustomColor()
{
    const auto eighth_length = leds.size() / 8;
    const auto center = (std::begin(leds) + (leds.size() / 2) + configs.ledstrip.centerOffset.value());

    std::fill(std::begin(leds), std::end(leds), configs.ledstrip.custom_color[int(Bobbycar_Side::FRONT)].value()); // Front
    std::fill(center - (eighth_length / 2), center + (eighth_length / 2), configs.ledstrip.custom_color[int(Bobbycar_Side::BACK)].value()); // Back

#ifdef LEDSTRIP_WRONG_DIRECTION
    std::fill(center + (eighth_length / 2), center + (eighth_length / 2) + eighth_length, configs.ledstrip.custom_color[int(Bobbycar_Side::BACK_LEFT)].value());  // Back Left
    std::fill(center - (eighth_length / 2) - eighth_length, center - (eighth_length / 2), configs.ledstrip.custom_color[int(Bobbycar_Side::BACK_RIGHT)].value()); // Back Right
#else
    std::fill(center + (eighth_length / 2), center + (eighth_length / 2) + eighth_length, configs.ledstrip.custom_color[int(Bobbycar_Side::BACK_RIGHT)].value());  // Back Right
    std::fill(center - (eighth_length / 2) - eighth_length, center - (eighth_length / 2), configs.ledstrip.custom_color[int(Bobbycar_Side::BACK_LEFT)].value());   // Back Left
#endif

#ifdef LEDSTRIP_WRONG_DIRECTION
    std::fill(center + (eighth_length / 2) + eighth_length, center + (eighth_length / 2) + eighth_length + eighth_length, configs.ledstrip.custom_color[int(Bobbycar_Side::LEFT)].value());  // Left
    std::fill(center - (eighth_length / 2) - eighth_length - eighth_length, center - (eighth_length / 2) - eighth_length, configs.ledstrip.custom_color[int(Bobbycar_Side::RIGHT)].value()); // Right
#else
    std::fill(center + (eighth_length / 2) + eighth_length, center + (eighth_length / 2) + eighth_length + eighth_length, configs.ledstrip.custom_color[int(Bobbycar_Side::RIGHT)].value());  // Right
    std::fill(center - (eighth_length / 2) - eighth_length - eighth_length, center - (eighth_length / 2) - eighth_length, configs.ledstrip.custom_color[int(Bobbycar_Side::LEFT)].value());   // Left
#endif

#ifdef LEDSTRIP_WRONG_DIRECTION
    std::fill(center + (eighth_length / 2) + eighth_length + eighth_length, center + (eighth_length / 2) + eighth_length + eighth_length + eighth_length, configs.ledstrip.custom_color[int(Bobbycar_Side::FRONT_LEFT)].value());  // Front Left
    std::fill(center - (eighth_length / 2) - eighth_length - eighth_length - eighth_length, center - (eighth_length / 2) - eighth_length - eighth_length, configs.ledstrip.custom_color[int(Bobbycar_Side::FRONT_RIGHT)].value()); // Front Right
#else
    std::fill(center + (eighth_length / 2) + eighth_length + eighth_length, center + (eighth_length / 2) + eighth_length + eighth_length + eighth_length, configs.ledstrip.custom_color[int(Bobbycar_Side::FRONT_RIGHT)].value());  // Front Right
    std::fill(center - (eighth_length / 2) - eighth_length - eighth_length - eighth_length, center - (eighth_length / 2) - eighth_length - eighth_length, configs.ledstrip.custom_color[int(Bobbycar_Side::FRONT_LEFT)].value());   // Front Left
#endif
}

void showPrideAnimation()
{
    const auto ledstrip_length = leds.size();
    static uint16_t sPseudotime{0};
    static espchrono::millis_clock::time_point sLastMillis{};
    static uint16_t sHue16{0};

    const uint8_t sat8 = beatsin88(87, 220, 250);
    const uint8_t brightdepth = beatsin88(341, 96, 224);
    const uint16_t brightnessthetainc16 = beatsin88(203, (25 * 256), (40 * 256));
    const uint8_t msmultiplier = beatsin88(147, 23, 60);

    uint16_t hue16 = sHue16;//gHue * 256;
    uint16_t hueinc16 = beatsin88(113, 1, 3000);

    const auto deltams = espchrono::ago(sLastMillis).count() / 1000;
    sLastMillis = espchrono::millis_clock::now();
    sPseudotime += deltams * msmultiplier;
    sHue16 += deltams * beatsin88( 400, 5, 9);
    uint16_t brightnesstheta16 = sPseudotime;

    for (uint16_t i = 0 ; i < ledstrip_length; i++) {
        hue16 += hueinc16;
        const uint8_t hue8 = hue16 / 256;

        brightnesstheta16  += brightnessthetainc16;
        const uint16_t b16 = sin16(brightnesstheta16) + 32768;

        const uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
        uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
        bri8 += (255 - brightdepth);

        const CRGB newcolor = CHSV( hue8, sat8, bri8);
        const uint16_t pixelnumber = (ledstrip_length - 1) - i;

        nblend(leds[pixelnumber], newcolor, 64);
    }
}

void showWarningAnimation()
{
    // breathing yellow
    const bool isOn = (espchrono::utc_clock::now().time_since_epoch() % 750ms < 350ms);
    static uint8_t brightness{0};

    // cubic easing
    brightness = isOn ? std::min(brightness + 2, 255) : std::max(brightness - 2, 0);

    CRGB color = CRGB::Yellow;

    color.r = (color.r * brightness) / 255;
    color.g = (color.g * brightness) / 255;
    color.b = (color.b * brightness) / 255;

    std::fill(leds.begin(), leds.end(), color);
}

void showDrehlichtAnimation()
{
    static uint16_t position{0};

    for (uint8_t i = 0; i < 15; i++) {
        leds[position] = CRGB::Yellow;
        position = (position + 1) % leds.size();
        fadeToBlackBy(leds.data(), leds.size(), 2);
    }

    fadeToBlackBy(leds.data(), leds.size(), 10);
}

void showMancheLKWShabensoeinelichtanimation()
{
    const auto now = espchrono::utc_clock::now();

    const bool is_links_und_nicht_rechts = (now.time_since_epoch() % 1600ms < 800ms);

    const auto is_an = (now.time_since_epoch() % 200ms < 100ms) && (now.time_since_epoch() % 800ms < 600ms);

    std::fill(std::begin(leds), std::end(leds), CRGB::Black);

    const auto center = (std::begin(leds) + (leds.size() / 2) + configs.ledstrip.centerOffset.value());

    if (is_links_und_nicht_rechts)
    {
        std::fill(center, std::end(leds), is_an ? CRGB::Yellow : CRGB::Black);
    }
    else
    {
        std::fill(std::begin(leds), center, is_an ? CRGB::Yellow : CRGB::Black);
    }
}

[[nodiscard]] bool activateAutomaticFrontLight()
{
    using namespace std::chrono_literals;
    if (!configs.ledstrip.automaticLight.value())
        return false;
    const auto today = toDateTime(espchrono::utc_clock::now());

    if (static_cast<int>(today.date.year()) < 2000)
        return true;

    if (!sunrise_dt || (*sunrise_dt).date.day() != today.date.day())
    {
        sunrise_dt = today;
        time::calculate_sun();
    }

    const int currentTimeInMinutes = today.hour * 60 + today.minute;
    return (currentTimeInMinutes <= sunrise || currentTimeInMinutes >= sunset);
}

} // namespace bobby::ledstrip
