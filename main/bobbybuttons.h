#pragma once

// system includes
#include <optional>

// 3rdparty lib includes
#include "buttonsinterface.h"

enum BobbyButton
{
    Profile0 = espgui::Button::ButtonMax + 1,
    Profile1,
    Profile2,
    Profile3,
    Left2,
    Right2,
    Up2,
    Down2,
    Extra1,
    Extra2,
    Extra3,
    Extra4,
    Confirm = espgui::Button::Right,
    Back = espgui::Button::Left
};

[[nodiscard]] std::optional<espgui::Button> translateRawButton(uint8_t button);
void buttonPressedCommon(espgui::Button button);
void buttonReleasedCommon(espgui::Button button);

class BobbyButtons : public virtual espgui::ButtonsInterface
{
public:
    void rawButtonPressed(uint8_t button) override;
    void rawButtonReleased(uint8_t button) override;

    void buttonPressed(espgui::Button button) override;
    void buttonReleased(espgui::Button button) override;
};
