#include "bobbybuttons.h"

// esp-idf includes
#include <esp_log.h>

// local includes
#include "newsettings.h"
#include "settingsutils.h"
#include "modes/defaultmode.h"
#include "ledstripdefines.h"
#include "ledstrip.h"

#include "bobbyquickactions.h"

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
    if (configs.dpadMappingExtra1.value == button)
        return Button(BobbyButton::Extra1);
    if (configs.dpadMappingExtra2.value == button)
        return Button(BobbyButton::Extra2);
    if (configs.dpadMappingExtra3.value == button)
        return Button(BobbyButton::Extra3);
    if (configs.dpadMappingExtra4.value == button)
        return Button(BobbyButton::Extra4);

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
    case BobbyButton::Right2:
    case BobbyButton::Up2:
    case BobbyButton::Down2:
    case BobbyButton::Extra1:
    case BobbyButton::Extra2:
    case BobbyButton::Extra3:
    case BobbyButton::Extra4:
        quickactions::handle_bobby_quickaction(button);
        break;
    default:;
    }
}

void buttonReleasedCommon(espgui::Button button)
{
    switch (BobbyButton(button))
    {
    case BobbyButton::Left2:
    case BobbyButton::Right2:
    case BobbyButton::Up2:
    case BobbyButton::Down2:
    case BobbyButton::Extra1:
    case BobbyButton::Extra2:
    case BobbyButton::Extra3:
    case BobbyButton::Extra4:
        quickactions::handle_bobby_quickaction(button, false);
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
    buttonReleasedCommon(button);
}
