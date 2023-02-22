#include "bobbybuttons.h"

// esp-idf includes
#include <esp_log.h>

// local includes
#include "bobbyquickactions.h"
#include "newsettings.h"
#include "screens.h"
#include "settingsutils.h"

namespace bobby {

namespace {
constexpr const char TAG[] = "BUTTONS";
} // namespace

std::optional<espchrono::millis_clock::time_point> buttonLeftHeld;
std::optional<espchrono::millis_clock::time_point> buttonRightHeld;
std::optional<espchrono::millis_clock::time_point> buttonUpHeld;
std::optional<espchrono::millis_clock::time_point> buttonDownHeld;

[[nodiscard]] std::optional<espgui::Button> translateRawButton(uint8_t button)
{
    // Invalid
    if (button == INPUT_MAPPING_NONE)
        return std::nullopt;

    using espgui::Button;
    if (configs.dpadMappingLeft.value() == button)
        return Button::Left;
    if (configs.dpadMappingRight.value() == button)
        return Button::Right;
    if (configs.dpadMappingUp.value() == button)
        return Button::Up;
    if (configs.dpadMappingDown.value() == button)
        return Button::Down;
    if (configs.dpadMappingProfile0.value() == button)
        return Button(BobbyButton::Profile0);
    if (configs.dpadMappingProfile1.value() == button)
        return Button(BobbyButton::Profile1);
    if (configs.dpadMappingProfile2.value() == button)
        return Button(BobbyButton::Profile2);
    if (configs.dpadMappingProfile3.value() == button)
        return Button(BobbyButton::Profile3);
    if (configs.dpadMappingLeft2.value() == button)
        return Button(BobbyButton::Left2);
    if (configs.dpadMappingRight2.value() == button)
        return Button(BobbyButton::Right2);
    if (configs.dpadMappingUp2.value() == button)
        return Button(BobbyButton::Up2);
    if (configs.dpadMappingDown2.value() == button)
        return Button(BobbyButton::Down2);
    if (configs.dpadMappingExtra1.value() == button)
        return Button(BobbyButton::Extra1);
    if (configs.dpadMappingExtra2.value() == button)
        return Button(BobbyButton::Extra2);
    if (configs.dpadMappingExtra3.value() == button)
        return Button(BobbyButton::Extra3);
    if (configs.dpadMappingExtra4.value() == button)
        return Button(BobbyButton::Extra4);

    ESP_LOGW(TAG, "unknown raw button %hhu", button);

    return std::nullopt;
}

void buttonPressedCommon(espgui::Button button)
{
    const auto now = espchrono::millis_clock::now();

    switch (button)
    {
        using namespace bobby;
    case espgui::Button::Left:
        buttonLeftHeld = now;
        break;
    case espgui::Button::Right:
        buttonRightHeld = now;
        break;
    case espgui::Button::Up:
        buttonUpHeld = now;
        break;
    case espgui::Button::Down:
        buttonDownHeld = now;
        break;
    }

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
    switch (button)
    {
        using namespace bobby;
        using namespace std::chrono_literals;
    case espgui::Button::Left:
        if (buttonLeftHeld && espchrono::ago(*buttonLeftHeld) > 500ms)
            handleButtonLongPress(button);
        buttonLeftHeld = std::nullopt;
        break;
    case espgui::Button::Right:
        if (buttonRightHeld && espchrono::ago(*buttonRightHeld) > 500ms)
            handleButtonLongPress(button);
        buttonRightHeld = std::nullopt;
        break;
    case espgui::Button::Up:
        if (buttonUpHeld && espchrono::ago(*buttonUpHeld) > 500ms)
            handleButtonLongPress(button);
        buttonUpHeld = std::nullopt;
        break;
    case espgui::Button::Down:
        if (buttonDownHeld && espchrono::ago(*buttonDownHeld) > 500ms)
            handleButtonLongPress(button);
        buttonDownHeld = std::nullopt;
        break;
    }

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

void handleButtonLongPress(espgui::Button button)
{
    ESP_LOGI(TAG, "long press %hhu", button);
    switch (button)
    {
    case espgui::Button::Left:
        //
        break;
    case espgui::Button::Right:
        bobby::tft_init_with_screen();
        break;
    case espgui::Button::Up:
        //
        break;
    case espgui::Button::Down:
        //
        break;
    default:;
    }
}

} // namespace bobby
