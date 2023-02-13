#pragma once

// system includes
#include <optional>

// 3rdparty lib includes
#include <buttonsinterface.h>
#include <espchrono.h>

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
    Back = espgui::Button::Left,
    ButtonMax = Back
};

namespace bobby {
extern std::optional<espchrono::millis_clock::time_point> buttonLeftHeld;
extern std::optional<espchrono::millis_clock::time_point> buttonRightHeld;
extern std::optional<espchrono::millis_clock::time_point> buttonUpHeld;
extern std::optional<espchrono::millis_clock::time_point> buttonDownHeld;
} // namespace bobby

[[nodiscard]] std::optional<espgui::Button> translateRawButton(uint8_t button);
void buttonPressedCommon(espgui::Button button);
void buttonReleasedCommon(espgui::Button button);
void handleButtonLongPress(espgui::Button button);
