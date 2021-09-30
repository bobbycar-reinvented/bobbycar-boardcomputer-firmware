#pragma once

// system includes
#include <optional>

// 3rdparty lib includes
#include <espchrono.h>

// local includes
#include "settingsutils.h"
#include "ledstripdefines.h"

#ifdef FEATURE_LEDSTRIP
#include "ledstrip.h"
#endif

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
        if (upPressedSince && espchrono::ago(*upPressedSince) > (upPressRepeat > 2 ? 50ms : 400ms))
        {
            upPressedSince = espchrono::millis_clock::now();
            upPressRepeat++;
            rotated -= 1;
        }

        if (downPressedSince && espchrono::ago(*downPressedSince) > (downPressRepeat > 2 ? 50ms : 400ms))
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

    static void blinkLeftButton(bool pressed){
        if(!pressed)return;

#ifdef FEATURE_LEDSTRIP
        if(blinkAnimation == LEDSTRIP_ANIMATION_DEFAULT){ //transition from off to left
            blinkAnimation = LEDSTRIP_ANIMATION_BLINKLEFT;
        }
        else if(blinkAnimation == LEDSTRIP_ANIMATION_BLINKRIGHT){ // transition to warning
            blinkAnimation = LEDSTRIP_ANIMATION_BLINKBOTH;
        }
        else{ // transition to off
            blinkAnimation = 0;
        }
#endif
    }

    static void blinkRightButton(bool pressed){
        if(!pressed)return;
#ifdef FEATURE_LEDSTRIP
        if(blinkAnimation == LEDSTRIP_ANIMATION_DEFAULT){ //transition from off to right
            blinkAnimation = LEDSTRIP_ANIMATION_BLINKRIGHT;
        }
        else if(blinkAnimation == LEDSTRIP_ANIMATION_BLINKLEFT){ // transition to warning
            blinkAnimation = LEDSTRIP_ANIMATION_BLINKBOTH;
        }
        else{ // transition to off
            blinkAnimation = 0;
        }
#endif
    }

    static void quickActionButtonDown(bool pressed){

    }

    static void quickActionButtonUp(bool pressed){

    }
};
}
