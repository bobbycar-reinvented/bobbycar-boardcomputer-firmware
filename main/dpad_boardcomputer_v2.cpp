#include "dpad_boardcomputer_v2.h"

// system includes
#include <array>

// Arduino includes
#include <Arduino.h>

// 3rdparty lib includes
#include <espchrono.h>
#include <tickchrono.h>
#include <screenmanager.h>

// local includes
#include "types.h"
#include "globals.h"
#include "newsettings.h"
#include "bobbybuttons.h"

namespace {
template<pin_t OUT1, pin_t OUT2, pin_t IN1, pin_t IN2, pin_t IN3, pin_t IN4>
class Helper
{
public:
    static constexpr auto Out1Pin = OUT1;
    static constexpr auto Out2Pin = OUT2;
    static constexpr auto In1Pin = IN1;
    static constexpr auto In2Pin = IN2;
    static constexpr auto In3Pin = IN3;
    static constexpr auto In4Pin = IN4;

    void begin();

    std::array<bool, 16> read();
};

template<pin_t OUT1, pin_t OUT2, pin_t IN1, pin_t IN2, pin_t IN3, pin_t IN4>
void Helper<OUT1, OUT2, IN1, IN2, IN3, IN4>::begin()
{
    pinMode(OUT1, OUTPUT);
    pinMode(OUT2, OUTPUT);
}

template<pin_t OUT1, pin_t OUT2, pin_t IN1, pin_t IN2, pin_t IN3, pin_t IN4>
std::array<bool, 16> Helper<OUT1, OUT2, IN1, IN2, IN3, IN4>::read()
{
    std::array<bool, 16> result;

    pinMode(OUT1, OUTPUT);
    pinMode(OUT2, INPUT);

    digitalWrite(OUT1, LOW);

    pinMode(IN1, INPUT_PULLUP);
    pinMode(IN2, INPUT_PULLUP);
    pinMode(IN3, INPUT_PULLUP);
    pinMode(IN4, INPUT_PULLUP);

    if (configs.buttonReadDelay.value != 0) {
        delayMicroseconds(configs.buttonReadDelay.value);
    } else {
        vPortYield();
    }

    result[0] = digitalRead(IN1)==LOW;
    result[1] = digitalRead(IN2)==LOW;
    result[2] = digitalRead(IN3)==LOW;
    result[3] = digitalRead(IN4)==LOW;

    digitalWrite(OUT1, HIGH);

    pinMode(IN1, INPUT_PULLDOWN);
    pinMode(IN2, INPUT_PULLDOWN);
    pinMode(IN3, INPUT_PULLDOWN);
    pinMode(IN4, INPUT_PULLDOWN);

    if (configs.buttonReadDelay.value != 0) {
        delayMicroseconds(configs.buttonReadDelay.value);
    } else {
        vPortYield();
    }

    result[4] = digitalRead(IN1);
    result[5] = digitalRead(IN2);
    result[6] = digitalRead(IN3);
    result[7] = digitalRead(IN4);

    digitalWrite(OUT1, LOW);
    pinMode(OUT1, INPUT);
    pinMode(OUT2, OUTPUT);

    digitalWrite(OUT2, LOW);

    pinMode(IN1, INPUT_PULLUP);
    pinMode(IN2, INPUT_PULLUP);
    pinMode(IN3, INPUT_PULLUP);
    pinMode(IN4, INPUT_PULLUP);

    if (configs.buttonReadDelay.value != 0) {
        delayMicroseconds(configs.buttonReadDelay.value);
    } else {
        vPortYield();
    }

    result[8] = digitalRead(IN1)==LOW;
    result[9] = digitalRead(IN2)==LOW;
    result[10] = digitalRead(IN3)==LOW;
    result[11] = digitalRead(IN4)==LOW;

    digitalWrite(OUT2, HIGH);

    pinMode(IN1, INPUT_PULLDOWN);
    pinMode(IN2, INPUT_PULLDOWN);
    pinMode(IN3, INPUT_PULLDOWN);
    pinMode(IN4, INPUT_PULLDOWN);

    if (configs.buttonReadDelay.value != 0) {
        delayMicroseconds(configs.buttonReadDelay.value);
    } else {
        vPortYield();
    }

    result[12] = digitalRead(IN1);
    result[13] = digitalRead(IN2);
    result[14] = digitalRead(IN3);
    result[15] = digitalRead(IN4);

    return result;
}

#ifdef DPAD_BOARDCOMPUTER_V2
Helper<PINS_DPAD_BOARDCOMPUTER_V2_OUT1, PINS_DPAD_BOARDCOMPUTER_V2_OUT2, PINS_DPAD_BOARDCOMPUTER_V2_IN1, PINS_DPAD_BOARDCOMPUTER_V2_IN2, PINS_DPAD_BOARDCOMPUTER_V2_IN3, PINS_DPAD_BOARDCOMPUTER_V2_IN4> helper;
std::array<bool, 16> lastState;
std::array<espchrono::millis_clock::time_point, 16> debounce;
#endif
} // namespace

#ifdef DPAD_BOARDCOMPUTER_V2
namespace dpad_boardcomputer_v2 {

void init()
{
    helper.begin();
    std::fill(std::begin(lastState), std::end(lastState), false);
    std::fill(std::begin(debounce), std::end(debounce), espchrono::millis_clock::now());
}

void update()
{
    const auto newState = helper.read();

#ifdef DPAD_BOARDCOMPUTER_V2_DEBUG

    if (newState != lastState) {
        ESP_LOGI("DPAD_BOARDCOMPUTER_V2", "new state: %s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s",
            newState[0] ? "1" : "0",
            newState[1] ? "1" : "0",
            newState[2] ? "1" : "0",
            newState[3] ? "1" : "0",
            newState[4] ? "1" : "0",
            newState[5] ? "1" : "0",
            newState[6] ? "1" : "0",
            newState[7] ? "1" : "0",
            newState[8] ? "1" : "0",
            newState[9] ? "1" : "0",
            newState[10] ? "1" : "0",
            newState[11] ? "1" : "0",
            newState[12] ? "1" : "0",
            newState[13] ? "1" : "0",
            newState[14] ? "1" : "0",
            newState[15] ? "1" : "0");
    }

    lastState = newState;
    return;
#endif

    const auto now = espchrono::millis_clock::now();

    const std::chrono::milliseconds dpadDebounce{configs.dpadDebounce.value};

    for (auto i = 0; i < newState.size(); i++)
        if (lastState[i] != newState[i] && now - debounce[i] > dpadDebounce)
        {
            lastState[i] = newState[i];
            if (espgui::currentDisplay)
            {
                if (newState[i])
                    espgui::currentDisplay->rawButtonPressed(i);
                else
                    espgui::currentDisplay->rawButtonReleased(i);
            }
            debounce[i] = now;
        }
}

} // namespace dpad_boardcomputer_v2

#endif
