#pragma once

// system includes
#include <optional>

// 3rdparty lib includes
#include <espchrono.h>

// local includes
#include "settingsutils.h"

namespace {

int rotated{};
bool requestFullRedraw{};

bool confirmButtonPressed{};
bool confirmButtonLongPressed{};
bool backButtonPressed{};
bool backButtonLongPressed{};

bool profileButtonDisabled{};

std::optional<espchrono::millis_clock::time_point> upPressedSince;
int upPressRepeat{};
std::optional<espchrono::millis_clock::time_point> downPressedSince;
int downPressRepeat{};

class InputDispatcher
{
public:
    static void update()
    {
        if (upPressedSince && espchrono::ago(*upPressedSince) > (upPressRepeat > 3 ? 100ms : 500ms))
        {
            upPressedSince = espchrono::millis_clock::now();
            upPressRepeat++;
            rotated -= 1;
        }

        if (downPressedSince && espchrono::ago(*downPressedSince) > (downPressRepeat > 3 ? 100ms : 500ms))
        {
            downPressedSince = espchrono::millis_clock::now();
            downPressRepeat++;
            rotated += 1;
        }
    }

    static void rotate(int offset)
    {
        rotated += offset;
    }

    static void upButton(bool pressed)
    {
        if (pressed)
        {
            upPressedSince = espchrono::millis_clock::now();
            upPressRepeat = 0;
            rotated -= 1;
        }
        else
        {
            upPressedSince = std::nullopt;
        }
    }

    static void downButton(bool pressed)
    {
        if (pressed)
        {
            downPressedSince = espchrono::millis_clock::now();
            downPressRepeat = 0;
            rotated += 1;
        }
        else
        {
            downPressedSince = std::nullopt;
        }
    }

    static void confirmButton(bool pressed)
    {
        static espchrono::millis_clock::time_point pressBegin{};

        const auto now = espchrono::millis_clock::now();

        if (pressed)
            pressBegin = now;
        else
        {
            const auto duration = now - pressBegin;

            if (duration < 500ms)
                confirmButtonPressed = true;
            else if (duration < 2000ms)
                confirmButtonLongPressed = true;
            else
                requestFullRedraw = true;

            pressBegin = {};
        }
    }

    static void backButton(bool pressed)
    {
        static espchrono::millis_clock::time_point pressBegin{};

        const auto now = espchrono::millis_clock::now();

        if (pressed)
            pressBegin = now;
        else
        {
            const auto duration = now - pressBegin;

            if (duration < 500ms)
                backButtonPressed = true;
            else
                backButtonLongPressed = true;

            pressBegin = {};
        }
    }

    static void profileButton(uint8_t index, bool pressed)
    {
        if (!pressed)
            return;

        if (profileButtonDisabled)
            return;

        switchProfile(index);
    }
};
}
