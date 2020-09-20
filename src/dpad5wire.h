#pragma once

#include <tuple>

#include <Arduino.h>

#include "globals.h"
#include "types.h"
#include "actions/switchprofileaction.h"

namespace {
namespace dpad5wire
{
using State = std::tuple<bool, bool, bool, bool, bool, bool, bool, bool>;

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
    digitalWrite(OUT, LOW);

    pinMode(IN1, INPUT_PULLUP);
    pinMode(IN2, INPUT_PULLUP);
    pinMode(IN3, INPUT_PULLUP);
    pinMode(IN4, INPUT_PULLUP);

    delay(1);

    const bool result0 = digitalRead(IN1)==LOW;
    const bool result1 = digitalRead(IN2)==LOW;
    const bool result2 = digitalRead(IN3)==LOW;
    const bool result3 = digitalRead(IN4)==LOW;

    digitalWrite(OUT, HIGH);

    pinMode(IN1, INPUT_PULLDOWN);
    pinMode(IN2, INPUT_PULLDOWN);
    pinMode(IN3, INPUT_PULLDOWN);
    pinMode(IN4, INPUT_PULLDOWN);

    delay(1);

    const bool result4 = digitalRead(IN1);
    const bool result5 = digitalRead(IN2);
    const bool result6 = digitalRead(IN3);
    const bool result7 = digitalRead(IN4);

    return std::make_tuple(result0, result1, result2, result3, result4, result5, result6, result7);
}

#ifdef FEATURE_DPAD_5WIRESW
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
    const auto state = helper.read();

#ifdef DPAD_5WIRESW_DEBUG
    lastState = state;
    return;
#endif

    const auto now = millis();

    if (std::get<DPAD_5WIRESW_UP>(lastState) != std::get<DPAD_5WIRESW_UP>(state) && now-debounceUp > settings.boardcomputerHardware.dpadDebounce)
    {
        if (std::get<DPAD_5WIRESW_UP>(state))
            InputDispatcher::rotate(-1);
        std::get<DPAD_5WIRESW_UP>(lastState) = std::get<DPAD_5WIRESW_UP>(state);
        debounceUp = now;
    }
    if (std::get<DPAD_5WIRESW_DOWN>(lastState) != std::get<DPAD_5WIRESW_DOWN>(state) && now-debounceDown > settings.boardcomputerHardware.dpadDebounce)
    {
        if (std::get<DPAD_5WIRESW_DOWN>(state))
            InputDispatcher::rotate(1);
        std::get<DPAD_5WIRESW_DOWN>(lastState) = std::get<DPAD_5WIRESW_DOWN>(state);
        debounceDown = now;
    }
    if (std::get<DPAD_5WIRESW_CONFIRM>(lastState) != std::get<DPAD_5WIRESW_CONFIRM>(state) && now-debounceConfirm > settings.boardcomputerHardware.dpadDebounce)
    {
        InputDispatcher::confirmButton(std::get<DPAD_5WIRESW_CONFIRM>(state));
        std::get<DPAD_5WIRESW_CONFIRM>(lastState) = std::get<DPAD_5WIRESW_CONFIRM>(state);
        debounceConfirm = now;
    }
    if (std::get<DPAD_5WIRESW_BACK>(lastState) != std::get<DPAD_5WIRESW_BACK>(state) && now-debounceBack > settings.boardcomputerHardware.dpadDebounce)
    {
        InputDispatcher::backButton(std::get<DPAD_5WIRESW_BACK>(state));
        std::get<DPAD_5WIRESW_BACK>(lastState) = std::get<DPAD_5WIRESW_BACK>(state);
        debounceBack = now;
    }
    if (std::get<DPAD_5WIRESW_PROFILE0>(lastState) != std::get<DPAD_5WIRESW_PROFILE0>(state) && now-debounceProfile0 > settings.boardcomputerHardware.dpadDebounce)
    {
        if (std::get<DPAD_5WIRESW_PROFILE0>(state))
        {
            SwitchProfileAction<0>{}.triggered();
        }
        std::get<DPAD_5WIRESW_PROFILE0>(lastState) = std::get<DPAD_5WIRESW_PROFILE0>(state);
        debounceProfile0 = now;
    }
    if (std::get<DPAD_5WIRESW_PROFILE1>(lastState) != std::get<DPAD_5WIRESW_PROFILE1>(state) && now-debounceProfile1 > settings.boardcomputerHardware.dpadDebounce)
    {
        if (std::get<DPAD_5WIRESW_PROFILE1>(state))
        {
            SwitchProfileAction<1>{}.triggered();
        }
        std::get<DPAD_5WIRESW_PROFILE1>(lastState) = std::get<DPAD_5WIRESW_PROFILE1>(state);
        debounceProfile1 = now;
    }
    if (std::get<DPAD_5WIRESW_PROFILE2>(lastState) != std::get<DPAD_5WIRESW_PROFILE2>(state) && now-debounceProfile2 > settings.boardcomputerHardware.dpadDebounce)
    {
        if (std::get<DPAD_5WIRESW_PROFILE2>(state))
        {
            SwitchProfileAction<2>{}.triggered();
        }
        std::get<DPAD_5WIRESW_PROFILE2>(lastState) = std::get<DPAD_5WIRESW_PROFILE2>(state);
        debounceProfile2 = now;
    }
    if (std::get<DPAD_5WIRESW_PROFILE3>(lastState) != std::get<DPAD_5WIRESW_PROFILE3>(state) && now-debounceProfile3 > settings.boardcomputerHardware.dpadDebounce)
    {
        if (std::get<DPAD_5WIRESW_PROFILE3>(state))
        {
            SwitchProfileAction<3>{}.triggered();
        }
        std::get<DPAD_5WIRESW_PROFILE3>(lastState) = std::get<DPAD_5WIRESW_PROFILE3>(state);
        debounceProfile3 = now;
    }
}
#endif
}
}
