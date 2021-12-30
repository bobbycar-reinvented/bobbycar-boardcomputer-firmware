#include "bobbybuttons.h"

// local includes
#include "newsettings.h"

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

    return std::nullopt;
}

void buttonPressedCommon(espgui::Button button)
{
    switch (BobbyButton(button))
    {
    case BobbyButton::Profile0: /* TODO */ break;
    case BobbyButton::Profile1: /* TODO */ break;
    case BobbyButton::Profile2: /* TODO */ break;
    case BobbyButton::Profile3: /* TODO */ break;
    case BobbyButton::Left2: /* TODO */ break;
    case BobbyButton::Right2: /* TODO */ break;
    case BobbyButton::Up2: /* TODO */ break;
    case BobbyButton::Down2: /* TODO */ break;
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
