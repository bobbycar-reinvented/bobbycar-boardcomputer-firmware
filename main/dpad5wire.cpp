#include "dpad5wire.h"

// system includes
#include <array>

// Arduino includes
#include <esp32-hal-gpio.h>

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

    std::array<bool, 8> read();
};

template<pin_t OUT, pin_t IN1, pin_t IN2, pin_t IN3, pin_t IN4>
void Helper<OUT, IN1, IN2, IN3, IN4>::begin()
{
    pinMode(OUT, OUTPUT);
}

template<pin_t OUT, pin_t IN1, pin_t IN2, pin_t IN3, pin_t IN4>
std::array<bool, 8> Helper<OUT, IN1, IN2, IN3, IN4>::read()
{
    std::array<bool, 8> result;

    digitalWrite(OUT, LOW);

    pinMode(IN1, INPUT_PULLUP);
    pinMode(IN2, INPUT_PULLUP);
    pinMode(IN3, INPUT_PULLUP);
    pinMode(IN4, INPUT_PULLUP);

    vPortYield();

    result[0] = digitalRead(IN1)==LOW;
    result[1] = digitalRead(IN2)==LOW;
    result[2] = digitalRead(IN3)==LOW;
    result[3] = digitalRead(IN4)==LOW;

    digitalWrite(OUT, HIGH);

    pinMode(IN1, INPUT_PULLDOWN);
    pinMode(IN2, INPUT_PULLDOWN);
    pinMode(IN3, INPUT_PULLDOWN);
    pinMode(IN4, INPUT_PULLDOWN);

    vPortYield();

    result[4] = digitalRead(IN1);
    result[5] = digitalRead(IN2);
    result[6] = digitalRead(IN3);
    result[7] = digitalRead(IN4);

    return result;
}

#ifdef FEATURE_DPAD_5WIRESW
Helper<PINS_DPAD_5WIRESW_OUT, PINS_DPAD_5WIRESW_IN1, PINS_DPAD_5WIRESW_IN2, PINS_DPAD_5WIRESW_IN3, PINS_DPAD_5WIRESW_IN4> helper;
std::array<bool, 8> lastState;
std::array<espchrono::millis_clock::time_point, 8> debounce;
#endif
} // namespace

#ifdef FEATURE_DPAD_5WIRESW
namespace dpad5wire {
void init()
{
    helper.begin();
    std::fill(std::begin(lastState), std::end(lastState), false);
    std::fill(std::begin(debounce), std::end(debounce), espchrono::millis_clock::now());
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

    for (auto i = 0; i < 8; i++)
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
} // namespace dpad5wire
#endif
