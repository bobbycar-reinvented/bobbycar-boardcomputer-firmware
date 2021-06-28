#pragma once

#include <array>

#include <Arduino.h>

#include "types.h"
#include "buttons.h"

namespace {
namespace dpad5wire {
#ifdef FEATURE_DPAD_5WIRESW
class State : public std::array<bool, 8>
{
public:
    State() : std::array<bool, 8>{false, false, false, false, false, false, false, false} {}
    State(const std::array<bool, 8> &other) : std::array<bool, 8>{} {}

    State &operator=(const std::array<bool, 8> &other)
    {
        std::array<bool, 8>::operator=(other);
        return *this;
    }

    State &operator=(const State &other)
    {
        std::array<bool, 8>::operator=(other);
        return *this;
    }

    bool &up{this->at(DPAD_5WIRESW_UP)};
    bool &down{this->at(DPAD_5WIRESW_DOWN)};
    bool &confirm{this->at(DPAD_5WIRESW_CONFIRM)};
    bool &back{this->at(DPAD_5WIRESW_BACK)};
    bool &profile0{this->at(DPAD_5WIRESW_PROFILE0)};
    bool &profile1{this->at(DPAD_5WIRESW_PROFILE1)};
    bool &profile2{this->at(DPAD_5WIRESW_PROFILE2)};
    bool &profile3{this->at(DPAD_5WIRESW_PROFILE3)};
};

template<pin_t OUT, pin_t IN1, pin_t IN2, pin_t IN3, pin_t IN4>
class Helper
{
public:
    static constexpr auto OutPin = OUT;
    static constexpr auto In1Pin = IN1;
    static constexpr auto In2Pin = IN2;
    static constexpr auto In3Pin = IN3;
    static constexpr auto In4Pin = IN4;

    void begin();

    State read();
};

template<pin_t OUT, pin_t IN1, pin_t IN2, pin_t IN3, pin_t IN4>
void Helper<OUT, IN1, IN2, IN3, IN4>::begin()
{
    pinMode(OUT, OUTPUT);
}

template<pin_t OUT, pin_t IN1, pin_t IN2, pin_t IN3, pin_t IN4>
State Helper<OUT, IN1, IN2, IN3, IN4>::read()
{
    State result;

    digitalWrite(OUT, LOW);

    pinMode(IN1, INPUT_PULLUP);
    pinMode(IN2, INPUT_PULLUP);
    pinMode(IN3, INPUT_PULLUP);
    pinMode(IN4, INPUT_PULLUP);

    delay(1);

    result[0] = digitalRead(IN1)==LOW;
    result[1] = digitalRead(IN2)==LOW;
    result[2] = digitalRead(IN3)==LOW;
    result[3] = digitalRead(IN4)==LOW;

    digitalWrite(OUT, HIGH);

    pinMode(IN1, INPUT_PULLDOWN);
    pinMode(IN2, INPUT_PULLDOWN);
    pinMode(IN3, INPUT_PULLDOWN);
    pinMode(IN4, INPUT_PULLDOWN);

    delay(1);

    result[4] = digitalRead(IN1);
    result[5] = digitalRead(IN2);
    result[6] = digitalRead(IN3);
    result[7] = digitalRead(IN4);

    return result;
}

Helper<PINS_DPAD_5WIRESW_OUT, PINS_DPAD_5WIRESW_IN1, PINS_DPAD_5WIRESW_IN2, PINS_DPAD_5WIRESW_IN3, PINS_DPAD_5WIRESW_IN4> helper;
State lastState;
millis_t debounceUp, debounceDown, debounceConfirm, debounceBack, debounceProfile0, debounceProfile1, debounceProfile2, debounceProfile3;

void init()
{
    helper.begin();
    debounceUp = debounceDown = debounceConfirm = debounceBack = debounceProfile0 = debounceProfile1 = debounceProfile2 = debounceProfile3 = millis();
}

void update()
{
    const auto newState = helper.read();

#ifdef DPAD_5WIRESW_DEBUG
    lastState = newState;
    return;
#endif

    const auto now = millis();

    if (lastState.up != newState.up && now-debounceUp > settings.boardcomputerHardware.dpadDebounce)
    {
        if (newState.up)
            InputDispatcher::rotate(-1);
        debounceUp = now;
    }

    if (lastState.down != newState.down && now-debounceDown > settings.boardcomputerHardware.dpadDebounce)
    {
        if (newState.down)
            InputDispatcher::rotate(1);
        debounceDown = now;
    }

    if (lastState.confirm != newState.confirm && now-debounceConfirm > settings.boardcomputerHardware.dpadDebounce)
    {
        InputDispatcher::confirmButton(std::get<DPAD_5WIRESW_CONFIRM>(newState));
        debounceConfirm = now;
    }

    if (lastState.back != newState.back && now-debounceBack > settings.boardcomputerHardware.dpadDebounce)
    {
        InputDispatcher::backButton(std::get<DPAD_5WIRESW_BACK>(newState));
        debounceBack = now;
    }

    if (lastState.profile0 != newState.profile0 && now-debounceProfile0 > settings.boardcomputerHardware.dpadDebounce)
    {
        InputDispatcher::profileButton(0, std::get<DPAD_5WIRESW_PROFILE0>(newState));
        debounceProfile0 = now;
    }

    if (lastState.profile1 != newState.profile1 && now-debounceProfile1 > settings.boardcomputerHardware.dpadDebounce)
    {
        InputDispatcher::profileButton(1, std::get<DPAD_5WIRESW_PROFILE1>(newState));
        debounceProfile1 = now;
    }

    if (lastState.profile2 != newState.profile2 && now-debounceProfile2 > settings.boardcomputerHardware.dpadDebounce)
    {
        InputDispatcher::profileButton(2, std::get<DPAD_5WIRESW_PROFILE2>(newState));
        debounceProfile2 = now;
    }

    if (lastState.profile3 != newState.profile3 && now-debounceProfile3 > settings.boardcomputerHardware.dpadDebounce)
    {
        InputDispatcher::profileButton(3, std::get<DPAD_5WIRESW_PROFILE3>(newState));
        debounceProfile3 = now;
    }

    lastState = newState;
}
#endif

} // namespace dpad5wire
} // namespace
