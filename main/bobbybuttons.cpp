#include "bobbybuttons.h"

// esp-idf includes
#include <esp_log.h>

// local includes
#include "newsettings.h"
#include "settingsutils.h"
#include "modes/defaultmode.h"
#ifdef FEATURE_LEDSTRIP
#include "ledstripdefines.h"
#include "ledstrip.h"
#endif

namespace {
constexpr const char TAG[] = "BUTTONS";
} // namespace

[[nodiscard]] std::optional<espgui::Button> translateRawButton(uint8_t button)
{
    // Invalid
    if (button == INPUT_MAPPING_NONE)
        return std::nullopt;

    using espgui::Button;
    if (configs.dpadMappingLeft.value == button)
        return Button::Left;
    if (configs.dpadMappingRight.value == button)
        return Button::Right;
    if (configs.dpadMappingUp.value == button)
        return Button::Up;
    if (configs.dpadMappingDown.value == button)
        return Button::Down;
    if (configs.dpadMappingProfile0.value == button)
        return Button(BobbyButton::Profile0);
    if (configs.dpadMappingProfile1.value == button)
        return Button(BobbyButton::Profile1);
    if (configs.dpadMappingProfile2.value == button)
        return Button(BobbyButton::Profile2);
    if (configs.dpadMappingProfile3.value == button)
        return Button(BobbyButton::Profile3);
    if (configs.dpadMappingLeft2.value == button)
        return Button(BobbyButton::Left2);
    if (configs.dpadMappingRight2.value == button)
        return Button(BobbyButton::Right2);
    if (configs.dpadMappingUp2.value == button)
        return Button(BobbyButton::Up2);
    if (configs.dpadMappingDown2.value == button)
        return Button(BobbyButton::Down2);

    ESP_LOGW(TAG, "unknown raw button %hhu", button);

    return std::nullopt;
}

void buttonPressedCommon(espgui::Button button)
{
    switch (BobbyButton(button))
    {
    case BobbyButton::Profile0:
        settingsutils::switchProfile(0);
        break;
    case BobbyButton::Profile1:
        settingsutils::switchProfile(1);
        break;
    case BobbyButton::Profile2:
        settingsutils::switchProfile(2);
        break;
    case BobbyButton::Profile3:
        settingsutils::switchProfile(3);
        break;
    case BobbyButton::Left2:
#ifdef FEATURE_LEDSTRIP
        if (blinkAnimation == LEDSTRIP_OVERWRITE_NONE) //transition from off to left
        {
            blinkAnimation = LEDSTRIP_OVERWRITE_BLINKLEFT;
        }
        else if (blinkAnimation == LEDSTRIP_OVERWRITE_BLINKRIGHT) // transition to warning
        {
            blinkAnimation = LEDSTRIP_OVERWRITE_BLINKBOTH;
        }
        else // transition to off
        {
            blinkAnimation = LEDSTRIP_OVERWRITE_NONE;
        }
#endif
        break;
    case BobbyButton::Right2:
#ifdef FEATURE_LEDSTRIP
        if (blinkAnimation == LEDSTRIP_OVERWRITE_NONE) //transition from off to right
        {
            blinkAnimation = LEDSTRIP_OVERWRITE_BLINKRIGHT;
        }
        else if (blinkAnimation == LEDSTRIP_OVERWRITE_BLINKLEFT) // transition to warning
        {
            blinkAnimation = LEDSTRIP_OVERWRITE_BLINKBOTH;
        }
        else // transition to off
        {
            blinkAnimation = LEDSTRIP_OVERWRITE_NONE;
        }
#endif
        break;
    case BobbyButton::Up2:
        if (settings.handbremse.enable)
        {
            using namespace handbremse;
            if (stateWish == StateWish::brake || angezogen)
                stateWish = StateWish::release;
            else
                stateWish = StateWish::brake;
            wishTimer = espchrono::millis_clock::now();
        }
        break;
    case BobbyButton::Down2:
        /* TODO */
        break;
    default:;
    }
}

void BobbyButtons::rawButtonPressed(uint8_t button)
{
    //Base::rawButtonPressed(button);
    if (const auto translated = translateRawButton(button))
        buttonPressed(*translated);
}

void BobbyButtons::rawButtonReleased(uint8_t button)
{
    //Base::rawButtonReleased(button);
    if (const auto translated = translateRawButton(button))
        buttonReleased(*translated);
}

void BobbyButtons::buttonPressed(espgui::Button button)
{
    //Base::buttonPressed(button);
    buttonPressedCommon(button);
}

void BobbyButtons::buttonReleased(espgui::Button button)
{
    //Base::buttonReleased(button);
}
