#pragma once

#include <tuple>

#include <Arduino.h>

#include "globals.h"

namespace {
using DPadState = std::tuple<bool, bool, bool, bool>;

template<pin_t IN1, pin_t IN2, pin_t IN3, pin_t IN4>
class DPadHelper
{
 public:
    void begin();

    DPadState read();
};

template<pin_t IN1, pin_t IN2, pin_t IN3, pin_t IN4>
void DPadHelper<IN1, IN2, IN3, IN4>::begin()
{
  pinMode(IN1, INPUT_PULLUP);
  pinMode(IN2, INPUT_PULLUP);
  pinMode(IN3, INPUT_PULLUP);
  pinMode(IN4, INPUT_PULLUP);
}

template<pin_t IN1, pin_t IN2, pin_t IN3, pin_t IN4>
DPadState DPadHelper<IN1, IN2, IN3, IN4>::read()
{
    const bool result0 = digitalRead(IN1);
    const bool result1 = digitalRead(IN2);
    const bool result2 = digitalRead(IN3);
    const bool result3 = digitalRead(IN4);

    return std::make_tuple(result0, result1, result2, result3);
}

#ifdef FEATURE_DPAD
DPadHelper<PINS_DPAD_UP, PINS_DPAD_DOWN, PINS_DPAD_CONFIRM, PINS_DPAD_BACK> dpad;

DPadState dpadLastState;
void updateDpad()
{
    const auto state = dpad.read();

    enum {
        ButtonUp = 0
        ButtonDown = 1,
        ButtonConfirm = 2,
        ButtonBack = 3,
    };

    if (std::get<ButtonUp>(dpadHackLastState) != std::get<ButtonUp>(state))
    {
        if (std::get<ButtonUp>(state))
            InputDispatcher::rotate(-1);
        std::get<ButtonUp>(dpadHackLastState) = std::get<ButtonUp>(state);
    }
    if (std::get<ButtonDown>(dpadHackLastState) != std::get<ButtonDown>(state))
    {
        if (std::get<ButtonDown>(state))
            InputDispatcher::rotate(1);
        std::get<ButtonDown>(dpadHackLastState) = std::get<ButtonDown>(state);
    }
    if (std::get<ButtonConfirm>(dpadHackLastState) != std::get<ButtonConfirm>(state))
    {
        InputDispatcher::confirmButton(std::get<ButtonConfirm>(state));
        std::get<ButtonConfirm>(dpadHackLastState) = std::get<ButtonConfirm>(state);
    }
    if (std::get<ButtonBack>(dpadHackLastState) != std::get<ButtonBack>(state))
    {
        InputDispatcher::backButton(std::get<ButtonBack>(state));
        std::get<ButtonBack>(dpadHackLastState) = std::get<ButtonBack>(state);
    }

    dpadLastState = state;
}
#endif
}
