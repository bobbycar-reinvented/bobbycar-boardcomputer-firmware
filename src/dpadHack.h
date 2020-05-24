#pragma once

#include <tuple>

#include <Arduino.h>

#include "globals.h"

#include "dpad.h"

namespace {

template<pin_t OUT, pin_t IN1, pin_t IN2>
class DPadHackHelper
{
public:
    static constexpr auto OutPin = OUT;
    static constexpr auto In1Pin = IN1;
    static constexpr auto In2Pin = IN2;

    void begin();

    DPadState read();
};

template<pin_t OUT, pin_t IN1, pin_t IN2>
void DPadHackHelper<OUT, IN1, IN2>::begin()
{
    pinMode(OUT, OUTPUT);
}

template<pin_t OUT, pin_t IN1, pin_t IN2>
DPadState DPadHackHelper<OUT, IN1, IN2>::read()
{
    digitalWrite(OUT, LOW);

    pinMode(IN1, INPUT_PULLUP);
    pinMode(IN2, INPUT_PULLUP);

    delay(1);

    const bool result0 = digitalRead(IN1)==LOW;
    const bool result1 = digitalRead(IN2)==LOW;

    digitalWrite(OUT, HIGH);

    pinMode(IN1, INPUT_PULLDOWN);
    pinMode(IN2, INPUT_PULLDOWN);

    delay(1);

    const bool result2 = digitalRead(IN1);
    const bool result3 = digitalRead(IN2);

    return std::make_tuple(result0, result1, result2, result3);
}

#ifdef FEATURE_3WIRESW
DPadHackHelper<PINS_3WIRESW_OUT, PINS_3WIRESW_IN1, PINS_3WIRESW_IN2> dpadHack;

DPadState lastState;
void updateDpadHack()
{
    const auto state = dpadHack.read();

    enum {
        ButtonUp = 3,
        ButtonDown = 0,
        ButtonConfirm = 1,
        ButtonBack = 2
    };

    if (!std::get<ButtonUp>(lastState) && std::get<ButtonUp>(state))
        InputDispatcher::rotate(-1);
    if (!std::get<ButtonDown>(lastState) && std::get<ButtonDown>(state))
        InputDispatcher::rotate(1);
    if (std::get<ButtonConfirm>(lastState) != std::get<ButtonConfirm>(state))
        InputDispatcher::confirmButton(std::get<ButtonConfirm>(state));
    if (std::get<ButtonBack>(lastState) != std::get<ButtonBack>(state))
        InputDispatcher::backButton(std::get<ButtonBack>(state));

    lastState = state;
}
#endif
}
