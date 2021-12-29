#include "bobbybuttons.h"

std::optional<espgui::Button> translateRawButton(uint8_t button)
{
    switch (button)
    {
    using espgui::Button;
    case 0: return Button::Left;
    case 1: return Button::Right;
    case 2: return Button::Up;
    case 3: return Button::Down;
    case 4: return Button(BobbyButton::Profile0);
    case 5: return Button(BobbyButton::Profile1);
    case 6: return Button(BobbyButton::Profile2);
    case 7: return Button(BobbyButton::Profile3);
    case 8: return Button(BobbyButton::Left2);
    case 9: return Button(BobbyButton::Right2);
    case 10: return Button(BobbyButton::Up2);
    case 11: return Button(BobbyButton::Down2);
    }

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
