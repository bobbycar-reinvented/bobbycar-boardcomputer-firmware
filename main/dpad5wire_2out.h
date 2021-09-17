#pragma once

// system includes
#include <array>

// Arduino includes
#include <Arduino.h>

// 3rdparty lib includes
#include <espchrono.h>
#include <tickchrono.h>

// local includes
#include "buttons.h"
#include "types.h"

namespace {
namespace dpad5wire_2out {

#ifdef FEATURE_DPAD_5WIRESW_2OUT
class State : public std::array<bool, 12>
{
public:
    State() : std::array<bool, 12>{false, false, false, false, false, false, false, false, false, false, false, false} {}
    State(const std::array<bool, 12> &other) : std::array<bool, 12>{} {}

    State &operator=(const std::array<bool, 12> &other)
    {
        std::array<bool, 12>::operator=(other);
        return *this;
    }

    State &operator=(const State &other)
    {
        std::array<bool, 12>::operator=(other);
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

    bool &blink_left{this->at(DPAD_5WIRESW_BLINK_RIGHT)};
    bool &blink_right{this->at(DPAD_5WIRESW_BLINK_LEFT)};
    bool &quickaction_down{this->at(DPAD_5WIRESW_QUICKACTION_DOWN)};
    bool &quickaction_up{this->at(DPAD_5WIRESW_QUICKACTION_UP)};
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

template<pin_t OUT1, pin_t OUT2, pin_t IN1, pin_t IN2, pin_t IN3>
void Helper<OUT1, OUT2, IN1, IN2, IN3>::begin()
{
}

template<pin_t OUT1, pin_t OUT2, pin_t IN1, pin_t IN2, pin_t IN3>
State Helper<OUT1, OUT2, IN1, IN2, IN3>::read()
{
    State result;

    pinMode(OUT1, OUTPUT);
    pinMode(OUT2, INPUT);

    digitalWrite(OUT1, LOW);

    pinMode(IN1, INPUT_PULLUP);
    pinMode(IN2, INPUT_PULLUP);
    pinMode(IN3, INPUT_PULLUP);

    vPortYield();

    result[0] = digitalRead(IN1)==LOW;
    result[1] = digitalRead(IN2)==LOW;
    result[2] = digitalRead(IN3)==LOW;

    digitalWrite(OUT1, HIGH);

    pinMode(IN1, INPUT_PULLDOWN);
    pinMode(IN2, INPUT_PULLDOWN);
    pinMode(IN3, INPUT_PULLDOWN);

    vPortYield();

    result[3] = digitalRead(IN1);
    result[4] = digitalRead(IN2);
    result[5] = digitalRead(IN3);

    pinMode(OUT1, INPUT);
    pinMode(OUT2, OUTPUT);

    digitalWrite(OUT2, LOW);

    pinMode(IN1, INPUT_PULLUP);
    pinMode(IN2, INPUT_PULLUP);
    pinMode(IN3, INPUT_PULLUP);

    vPortYield();

    result[6] = digitalRead(IN1)==LOW;
    result[7] = digitalRead(IN2)==LOW;
    result[8] = digitalRead(IN3)==LOW;

    digitalWrite(OUT2, HIGH);

    pinMode(IN1, INPUT_PULLDOWN);
    pinMode(IN2, INPUT_PULLDOWN);
    pinMode(IN3, INPUT_PULLDOWN);

    vPortYield();

    result[9] = digitalRead(IN1);
    result[10] = digitalRead(IN2);
    result[11] = digitalRead(IN3);

    return result;
}

Helper<PINS_DPAD_5WIRESW_OUT1, PINS_DPAD_5WIRESW_OUT2, PINS_DPAD_5WIRESW_IN1, PINS_DPAD_5WIRESW_IN2, PINS_DPAD_5WIRESW_IN3> helper;
State lastState;
espchrono::millis_clock::time_point debounceUp, debounceDown, debounceConfirm, debounceBack, debounceProfile0, debounceProfile1, debounceProfile2, debounceProfile3, debounceBlinkLeft, debounceBlinkRight, debounceQuickactionDown, debounceQuickactionUp;

void init()
{
    helper.begin();
    debounceUp =
            debounceDown =
                    debounceConfirm =
                            debounceBack =
                                    debounceProfile0 =
                                            debounceProfile1 =
                                                    debounceProfile2 =
                                                            debounceProfile3 =
                                                                    debounceBlinkLeft=
                                                                            debounceBlinkRight =
                                                                                    debounceQuickactionDown =
                                                                                            debounceQuickactionUp =
                                                                                                    espchrono::millis_clock::now();
}

void update()
{
    const auto newState = helper.read();

#ifdef DPAD_5WIRESW_DEBUG
    lastState = newState;
    return;
#endif

    const auto now = espchrono::millis_clock::now();

    const std::chrono::milliseconds dpadDebounce{settings.boardcomputerHardware.dpadDebounce};

    if (lastState.up != newState.up && now - debounceUp > dpadDebounce)
    {
        lastState.up = newState.up;
        InputDispatcher::upButton(newState.up);
        debounceUp = now;
    }

    if (lastState.down != newState.down && now - debounceDown > dpadDebounce)
    {
        lastState.down = newState.down;
        InputDispatcher::downButton(newState.down);
        debounceDown = now;
    }

    if (lastState.confirm != newState.confirm && now - debounceConfirm > dpadDebounce)
    {
        lastState.confirm = newState.confirm;
        InputDispatcher::confirmButton(newState.confirm);
        debounceConfirm = now;
    }

    if (lastState.back != newState.back && now - debounceBack > dpadDebounce)
    {
        lastState.back = newState.back;
        InputDispatcher::backButton(newState.back);
        debounceBack = now;
    }

    if (lastState.profile0 != newState.profile0 && now - debounceProfile0 > dpadDebounce)
    {
        lastState.profile0 = newState.profile0;
        InputDispatcher::profileButton(0, newState.profile0);
        debounceProfile0 = now;
    }

    if (lastState.profile1 != newState.profile1 && now - debounceProfile1 > dpadDebounce)
    {
        lastState.profile1 = newState.profile1;
        InputDispatcher::profileButton(1, newState.profile1);
        debounceProfile1 = now;
    }

    if (lastState.profile2 != newState.profile2 && now - debounceProfile2 > dpadDebounce)
    {
        lastState.profile2 = newState.profile2;
        InputDispatcher::profileButton(2, newState.profile2);
        debounceProfile2 = now;
    }

    if (lastState.profile3 != newState.profile3 && now - debounceProfile3 > dpadDebounce)
    {
        lastState.profile3 = newState.profile3;
        InputDispatcher::profileButton(3, newState.profile3);
        debounceProfile3 = now;
    }

    if (lastState.blink_left != newState.blink_left && now - debounceBlinkLeft > dpadDebounce)
    {
        lastState.blink_left = newState.blink_left;
        debounceBlinkLeft = now;
    }

    if (lastState.blink_right != newState.blink_right && now - debounceBlinkRight > dpadDebounce)
    {
        lastState.blink_right = newState.blink_right;
        debounceBlinkRight = now;
    }

    if (lastState.quickaction_down != newState.quickaction_down && now - debounceQuickactionDown > dpadDebounce)
    {
        lastState.quickaction_down = newState.quickaction_down;
        debounceQuickactionDown = now;
    }

    if (lastState.quickaction_up != newState.quickaction_up && now - debounceQuickactionUp > dpadDebounce)
    {
        lastState.quickaction_up = newState.quickaction_up;
        debounceQuickactionUp = now;
    }
}
#endif

} // namespace dpad5wire_2out
} // namespace
