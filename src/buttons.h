#pragma once

// Arduino includes
#include <Arduino.h>

// local includes
#include "types.h"
#include "settingsutils.h"

namespace {

int rotated{};
bool requestFullRedraw{};

bool confirmButtonPressed{};
bool confirmButtonLongPressed{};
bool backButtonPressed{};
bool backButtonLongPressed{};

class InputDispatcher
{
public:
    static void rotate(int offset)
    {
        rotated += offset;
    }

    static void confirmButton(bool pressed)
    {
        static millis_t pressBegin = 0;

        const auto now = millis();

        if (pressed)
            pressBegin = now;
        else
        {
            const auto duration = now - pressBegin;

            if (duration < 500)
                confirmButtonPressed = true;
            else if (duration < 2000)
                confirmButtonLongPressed = true;
            else
                requestFullRedraw = true;

            pressBegin = 0;
        }
    }

    static void backButton(bool pressed)
    {
        static millis_t pressBegin = 0;

        const auto now = millis();

        if (pressed)
            pressBegin = now;
        else
        {
            const auto duration = now - pressBegin;

            if (duration < 500)
                backButtonPressed = true;
            else
                backButtonLongPressed = true;

            pressBegin = 0;
        }
    }

    static void profileButton(uint8_t index, bool pressed)
    {
        if (!pressed)
            return;

        switchProfile(index);
    }
};
}
