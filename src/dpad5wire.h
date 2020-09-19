#pragma once

#include <tuple>

#include <Arduino.h>
#include <HardwareSerial.h>

#include "globals.h"
#include "types.h"

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

    pinMode(IN1, INPUT_PULLUP);
    pinMode(IN2, INPUT_PULLUP);
    pinMode(IN3, INPUT_PULLUP);
    pinMode(IN4, INPUT_PULLUP);

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
    const auto now = millis();

    enum {
        ButtonUp = 3,
        ButtonDown = 0,
        ButtonConfirm = 1,
        ButtonBack = 2,
        ButtonProfile0 = 4,
        ButtonProfile1 = 5,
        ButtonProfile2 = 6,
        ButtonProfile3 = 7,
    };

    if (std::get<ButtonUp>(lastState) != std::get<ButtonUp>(state) && now-debounceUp > settings.boardcomputerHardware.dpadDebounce)
    {
        if (std::get<ButtonUp>(state))
            InputDispatcher::rotate(-1);
        std::get<ButtonUp>(lastState) = std::get<ButtonUp>(state);
        debounceUp = now;
    }
    if (std::get<ButtonDown>(lastState) != std::get<ButtonDown>(state) && now-debounceDown > settings.boardcomputerHardware.dpadDebounce)
    {
        if (std::get<ButtonDown>(state))
            InputDispatcher::rotate(1);
        std::get<ButtonDown>(lastState) = std::get<ButtonDown>(state);
        debounceDown = now;
    }
    if (std::get<ButtonConfirm>(lastState) != std::get<ButtonConfirm>(state) && now-debounceConfirm > settings.boardcomputerHardware.dpadDebounce)
    {
        InputDispatcher::confirmButton(std::get<ButtonConfirm>(state));
        std::get<ButtonConfirm>(lastState) = std::get<ButtonConfirm>(state);
        debounceConfirm = now;
    }
    if (std::get<ButtonBack>(lastState) != std::get<ButtonBack>(state) && now-debounceBack > settings.boardcomputerHardware.dpadDebounce)
    {
        InputDispatcher::backButton(std::get<ButtonBack>(state));
        std::get<ButtonBack>(lastState) = std::get<ButtonBack>(state);
        debounceBack = now;
    }
    if (std::get<ButtonProfile0>(lastState) != std::get<ButtonProfile0>(state) && now-debounceProfile0 > settings.boardcomputerHardware.dpadDebounce)
    {
        if (std::get<ButtonProfile0>(state))
        {
            if (settingsPersister.openProfile(0))
            {
                if (!settingsPersister.load(settings))
                    Serial.println("dpad5wire::update() load 0 failed");
            }
            else
                Serial.println("dpad5wire::update() openProfile 0 failed");
        }
        std::get<ButtonProfile0>(lastState) = std::get<ButtonProfile0>(state);
        debounceProfile0 = now;
    }
    if (std::get<ButtonProfile1>(lastState) != std::get<ButtonProfile1>(state) && now-debounceProfile1 > settings.boardcomputerHardware.dpadDebounce)
    {
        if (std::get<ButtonProfile1>(state))
        {
            if (settingsPersister.openProfile(1))
            {
                if (!settingsPersister.load(settings))
                    Serial.println("dpad5wire::update() load 1 failed");
            }
            else
                Serial.println("dpad5wire::update() openProfile 1 failed");
        }
        std::get<ButtonProfile1>(lastState) = std::get<ButtonProfile1>(state);
        debounceProfile1 = now;
    }
    if (std::get<ButtonProfile2>(lastState) != std::get<ButtonProfile2>(state) && now-debounceProfile2 > settings.boardcomputerHardware.dpadDebounce)
    {
        if (std::get<ButtonProfile2>(state))
        {
            if (settingsPersister.openProfile(2))
            {
                if (!settingsPersister.load(settings))
                    Serial.println("dpad5wire::update() load 2 failed");
            }
            else
                Serial.println("dpad5wire::update() openProfile 2 failed");
        }
        std::get<ButtonProfile2>(lastState) = std::get<ButtonProfile2>(state);
        debounceProfile2 = now;
    }
    if (std::get<ButtonProfile3>(lastState) != std::get<ButtonProfile3>(state) && now-debounceProfile3 > settings.boardcomputerHardware.dpadDebounce)
    {
        if (std::get<ButtonProfile3>(state))
        {
            if (settingsPersister.openProfile(3))
            {
                if (!settingsPersister.load(settings))
                    Serial.println("dpad5wire::update() load 3 failed");
            }
            else
                Serial.println("dpad5wire::update() openProfile 3 failed");
        }
        std::get<ButtonProfile3>(lastState) = std::get<ButtonProfile3>(state);
        debounceProfile3 = now;
    }
}
#endif
}
}
