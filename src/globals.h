#pragma once

#include <array>

#include <BluetoothSerial.h>
#include <WiFiType.h>
#include <TFT_eSPI.h>
#include <SPI.h>

#include "controller.h"
#include "display.h"
#include "modeinterface.h"
#include "settings.h"
#include "settingssaver.h"
#include "types.h"

namespace {
int16_t raw_gas, raw_brems;
float gas, brems;
#ifdef FEATURE_GAMETRAK
int16_t raw_gametrakX, raw_gametrakY, raw_gametrakDist;
float gametrakX, gametrakY, gametrakDist;
#endif
float avgSpeed, avgSpeedKmh, sumCurrent, sumAbsoluteCurrent;

char deviceName[32];

Settings settings;
SettingsSaver settingsSaver;

class Controllers : public std::array<Controller, 2>
{
public:
    explicit Controllers() :
        std::array<Controller, 2>{{
            Controller{Serial1, settings.controllerHardware.enableFrontLeft, settings.controllerHardware.enableFrontRight, settings.controllerHardware.invertFrontLeft, settings.controllerHardware.invertFrontRight},
            Controller{Serial2, settings.controllerHardware.enableBackLeft, settings.controllerHardware.enableBackRight, settings.controllerHardware.invertBackLeft, settings.controllerHardware.invertBackRight}
        }},
        front{getFront()},
        back(getBack())
    {}
    Controllers(const Controllers &) = delete;
    Controllers &operator=(const Controllers &) = delete;

    Controller &front;
    Controller &back;

private:
    Controller &getFront() { return operator[](0); }
    Controller &getBack() { return operator[](1); }
};

Controllers controllers;
struct FrontControllerGetter { static Controller &get() { return controllers.front; }};
struct BackControllerGetter { static Controller &get() { return controllers.back; }};

struct {
    millis_t lastTime = millis();
    int current{0};
    int last{0};
} performance;

BluetoothSerial bluetoothSerial;

TFT_eSPI tft = TFT_eSPI();

ModeInterface *currentMode{};

Display *currentDisplay{};

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
};
}
