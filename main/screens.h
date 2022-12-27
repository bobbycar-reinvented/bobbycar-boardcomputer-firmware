#pragma once

// system includes
#include <cstdint>
#include <string_view>

// esp-idf includes
#ifdef FEATURE_LEDBACKLIGHT
#include <hal/gpio_types.h>
#include <driver/ledc.h>
#include <hal/adc_types.h>
#endif

// 3rdparty lib includes
#include <widgets/label.h>

namespace bobby {

#ifdef FEATURE_LEDBACKLIGHT
namespace display {
constexpr auto displayBacklightPin = PINS_LEDBACKLIGHT;
constexpr auto displayBacklightChannel = ledc_channel_t::LEDC_CHANNEL_0;
constexpr auto displayBacklightFrequency = 5000;
constexpr auto displayBacklightResolution = ledc_timer_bit_t::LEDC_TIMER_13_BIT;
constexpr auto displayFadeDivider = 18;
constexpr auto displayMaxDuty = (1 << displayBacklightResolution);

extern uint8_t currentBrightness;

int fixDuty(int duty);
void disableBacklight(bool disable);
bool backlightDisabled();
} // namespace display
#endif

extern espgui::Label bootLabel;

void tft_init();
void initScreen();
void updateDisplay();
void updateRotation();
void redrawDisplay();
void disableScreenFlip(bool enable);

void set_boot_msg(std::string_view msg);
uint16_t getScreenWidth();
uint16_t getScreenHeight();
} // namespace bobby
