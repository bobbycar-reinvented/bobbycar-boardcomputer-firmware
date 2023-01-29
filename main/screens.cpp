#include "screens.h"

// esp-idf includes
#ifdef FEATURE_LEDBACKLIGHT
#include <driver/ledc.h>
#include <esp32-hal-gpio.h>
#include <esp_log.h>
#endif

// 3rdparty lib includes
#include <TFT_eSPI.h>
#include <fontrenderer.h>
#include <screenmanager.h>
#include <tftcolors.h>
#include <tftinterface.h>

// local includes
#include "globals.h"
#include "icons/logo.h"
#include "texthelpers/esptexthelpers.h"

namespace bobby {

namespace {
constexpr const char * const TAG = "DIPSLAY_BOBBY";
}

#ifdef FEATURE_LEDBACKLIGHT
namespace display {
uint8_t currentBrightness{0};

bool backlight_disabled{false};

int fixDuty(int duty)
{
    if (ledBacklightInverted)
        return displayMaxDuty - duty;
    return duty;
}

void disableBacklight(bool disable)
{
    backlight_disabled = disable;
}
bool backlightDisabled()
{
    return backlight_disabled;
}
} // namespace display
#endif

using namespace espgui;

espgui::Label bootLabel{32, 250};

namespace {
bool disable_screen_flip{false};

TFT_eSPI tft;
}

void tft_init()
{
    tft.init();
}

void initScreen()
{
#ifdef FEATURE_LEDBACKLIGHT
    ledc_timer_config_t display_backlight{
            .speed_mode = LEDC_LOW_SPEED_MODE,
            .duty_resolution = display::displayBacklightResolution,
            .timer_num = LEDC_TIMER_0,
            .freq_hz = display::displayBacklightFrequency,
            .clk_cfg = LEDC_AUTO_CLK,
    };

    if (const auto res = ledc_timer_config(&display_backlight); res != ESP_OK)
        ESP_LOGE(TAG, "ledc_timer_config() failed with %s", esp_err_to_name(res));
    else
        ESP_LOGI(TAG, "ledc_timer_config() succeeded");

    ledc_channel_config_t display_backlight_channel{
            .gpio_num = display::displayBacklightPin,
            .speed_mode = LEDC_LOW_SPEED_MODE,
            .channel = display::displayBacklightChannel,
            .intr_type = LEDC_INTR_DISABLE,
            .timer_sel = LEDC_TIMER_0,
            .duty = 0,
            .hpoint = 0,
    };

    if (const auto res = ledc_channel_config(&display_backlight_channel); res != ESP_OK)
        ESP_LOGE(TAG, "ledc_channel_config() failed with %s", esp_err_to_name(res));
    else
        ESP_LOGI(TAG, "ledc_channel_config() succeeded");

    if (const auto res = ledc_set_duty(LEDC_LOW_SPEED_MODE, display::displayBacklightChannel, display::fixDuty(0)); res != ESP_OK)
        ESP_LOGE(TAG, "ledc_set_duty() failed with %s", esp_err_to_name(res));
    else
        ESP_LOGI(TAG, "ledc_set_duty() succeeded");

    if (const auto res = ledc_update_duty(LEDC_LOW_SPEED_MODE, display::displayBacklightChannel); res != ESP_OK)
        ESP_LOGE(TAG, "ledc_update_duty() failed with %s", esp_err_to_name(res));
    else
        ESP_LOGI(TAG, "ledc_update_duty() succeeded");
#endif

    // vertical screen
    tft.init();
    ESP_LOGI(TAG, "TFT init done");

    tft.fillScreen(espgui::TFT_WHITE);
    ESP_LOGI(TAG, "TFT fill screen done");

    tft.setRotation(configs.boardcomputerHardware.flipScreen.value() ? 2 : 0);
    ESP_LOGI(TAG, "TFT rotation done");

    tft.pushImage(0, 40, bobbyicons::logo.WIDTH, bobbyicons::logo.HEIGHT, bobbyicons::logo.buffer);
    ESP_LOGI(TAG, "TFT push image done");

    auto renderer = espgui::FontRenderer{tft};

    renderer.drawString("Bobbycar-OS", 32, 200, espgui::TFT_BLACK, espgui::TFT_WHITE, 4);
    renderer.drawString("booting...", 32, 225, espgui::TFT_BLACK, espgui::TFT_WHITE, 4);
    renderer.drawString("last reboot reason:", 32, 275, espgui::TFT_BLACK, espgui::TFT_WHITE, 2);
    renderer.drawString(espcpputils::toString(esp_reset_reason()), 32, 295, espgui::TFT_BLACK, espgui::TFT_WHITE, 2);
    bootLabel.start(tft);

#ifdef FEATURE_LEDBACKLIGHT
    if (const auto res = ledc_set_duty(LEDC_LOW_SPEED_MODE, display::displayBacklightChannel, display::fixDuty(display::displayMaxDuty)); res != ESP_OK)
        ESP_LOGE(TAG, "ledc_set_duty() failed with %s", esp_err_to_name(res));
    else
        ESP_LOGI(TAG, "ledc_set_duty() succeeded");

    if (const auto res = ledc_update_duty(LEDC_LOW_SPEED_MODE, display::displayBacklightChannel); res != ESP_OK)
        ESP_LOGE(TAG, "ledc_update_duty() failed with %s", esp_err_to_name(res));
    else
        ESP_LOGI(TAG, "ledc_update_duty() succeeded");
#endif
}

void updateRotation()
{
    if (tft.getRotation() != (configs.boardcomputerHardware.flipScreen.value() ? 2 : 0))
    {
        tft.setRotation(configs.boardcomputerHardware.flipScreen.value() ? 2 : 0);
        if (currentDisplay)
            currentDisplay->initScreen(tft);
    }
}

void updateDisplay()
{
#ifdef FEATURE_LEDBACKLIGHT
    if (!display::backlightDisabled() && configs.boardcomputerHardware.display_brightness.value() != display::currentBrightness)
    {
        using namespace display;
        currentBrightness += (configs.boardcomputerHardware.display_brightness.value() > currentBrightness) ? std::max(1, (configs.boardcomputerHardware.display_brightness.value() - currentBrightness) / 10) : std::min(-1, (configs.boardcomputerHardware.display_brightness.value() - currentBrightness) / display::displayFadeDivider);

        if (const auto res = ledc_set_duty(LEDC_LOW_SPEED_MODE, display::displayBacklightChannel, fixDuty(currentBrightness * display::displayMaxDuty / 100)); res != ESP_OK)
            ESP_LOGE(TAG, "ledc_set_duty() failed with %s", esp_err_to_name(res));

        if (const auto res = ledc_update_duty(LEDC_LOW_SPEED_MODE, display::displayBacklightChannel); res != ESP_OK)
            ESP_LOGE(TAG, "ledc_update_duty() failed with %s", esp_err_to_name(res));
    }
    else if (display::backlightDisabled() && display::currentBrightness != 0)
    {
        using namespace display;
        currentBrightness = 0;

        if (const auto res = ledc_set_duty(LEDC_LOW_SPEED_MODE, display::displayBacklightChannel, fixDuty(currentBrightness * display::displayMaxDuty / 100)); res != ESP_OK)
            ESP_LOGE(TAG, "ledc_set_duty() failed with %s", esp_err_to_name(res));

        if (const auto res = ledc_update_duty(LEDC_LOW_SPEED_MODE, display::displayBacklightChannel); res != ESP_OK)
            ESP_LOGE(TAG, "ledc_update_duty() failed with %s", esp_err_to_name(res));
    }
#endif

    if (currentDisplay)
        currentDisplay->update();

    if (changeScreenCallback)
    {
        changeScreenCallback(tft);
        changeScreenCallback = {};
    }

    if (!disable_screen_flip)
        updateRotation();

    if (const int8_t rawButton = rawButtonRequest.load(); rawButton != -1 && currentDisplay)
    {
        currentDisplay->rawButtonPressed(rawButton);
        currentDisplay->rawButtonReleased(rawButton);
        rawButtonRequest = -1;
    }

    if (const int8_t button = buttonRequest.load(); button != -1 && currentDisplay)
    {
        const auto btn = espgui::Button(button);
        currentDisplay->buttonPressed(btn);
        currentDisplay->buttonReleased(btn);
        buttonRequest = -1;
    }

    if (initScreenRequest && currentDisplay)
    {
        currentDisplay->initScreen(tft);
        initScreenRequest = false;
    }
}

void redrawDisplay()
{
    if (currentDisplay)
    {
        currentDisplay->redraw(tft);
    }
}

void disableScreenFlip(bool enable)
{
    disable_screen_flip = enable;
}

void set_boot_msg(std::string_view msg)
{
    bootLabel.redraw(tft, msg, espgui::TFT_BLACK, espgui::TFT_WHITE, 4);
}

uint16_t getScreenWidth()
{
    return tft.width();
}

uint16_t getScreenHeight()
{
    return tft.height();
}
} // namespace bobby
