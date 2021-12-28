#include "bobbymenudisplay.h"

void BobbyMenuDisplay::rawButtonPressed(uint8_t button)
{
    Base::rawButtonPressed(button);
    switch (button)
    {
        using espgui::Button;
    case 0: buttonPressed(Button::Left); break;
    case 1: buttonPressed(Button::Right); break;
    case 2: buttonPressed(Button::Up); break;
    case 3: buttonPressed(Button::Down); break;
    case 4: buttonPressed(Button(BobbyButton::Profile0)); break;
    case 5: buttonPressed(Button(BobbyButton::Profile1)); break;
    case 6: buttonPressed(Button(BobbyButton::Profile2)); break;
    case 7: buttonPressed(Button(BobbyButton::Profile3)); break;
    case 8: buttonPressed(Button(BobbyButton::Left2)); break;
    case 9: buttonPressed(Button(BobbyButton::Right2)); break;
    case 10: buttonPressed(Button(BobbyButton::Up2)); break;
    case 11: buttonPressed(Button(BobbyButton::Down2)); break;
    }
}

void BobbyMenuDisplay::rawButtonReleased(uint8_t button)
{
    Base::rawButtonReleased(button);
    switch (button)
    {
        using espgui::Button;
    case 0: buttonReleased(Button::Left); break;
    case 1: buttonReleased(Button::Right); break;
    case 2: buttonReleased(Button::Up); break;
    case 3: buttonReleased(Button::Down); break;
    case 4: buttonReleased(Button(BobbyButton::Profile0)); break;
    case 5: buttonReleased(Button(BobbyButton::Profile1)); break;
    case 6: buttonReleased(Button(BobbyButton::Profile2)); break;
    case 7: buttonReleased(Button(BobbyButton::Profile3)); break;
    case 8: buttonReleased(Button(BobbyButton::Left2)); break;
    case 9: buttonReleased(Button(BobbyButton::Right2)); break;
    case 10: buttonReleased(Button(BobbyButton::Up2)); break;
    case 11: buttonReleased(Button(BobbyButton::Down2)); break;
    }
}

void BobbyMenuDisplay::buttonPressed(espgui::Button button)
{
    Base::buttonPressed(button);

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

void BobbyMenuDisplay::buttonReleased(espgui::Button button)
{
    Base::buttonReleased(button);
}
