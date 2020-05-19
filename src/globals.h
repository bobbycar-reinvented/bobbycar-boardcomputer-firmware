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

namespace {
using pin_t = int;

int16_t raw_gas, raw_brems;
float gas, brems;
float avgSpeed, avgSpeedKmh, sumCurrent, sumAbsoluteCurrent;

Settings settings;
SettingsSaver settingsSaver;

Controller front{Serial1, settings.controllerHardware.enableFrontLeft, settings.controllerHardware.enableFrontRight, settings.controllerHardware.invertFrontLeft, settings.controllerHardware.invertFrontRight};
Controller back{Serial2, settings.controllerHardware.enableBackLeft, settings.controllerHardware.enableBackRight, settings.controllerHardware.invertBackLeft, settings.controllerHardware.invertBackRight};

struct {
    unsigned long lastTime = millis();
    int current{0};
    int last{0};
} performance;

BluetoothSerial bluetoothSerial;

TFT_eSPI tft = TFT_eSPI();

ModeInterface *currentMode{};

Display *currentDisplay{};

int rotated{};
bool requestFullRedraw{};
bool buttonLongPressed{};
bool buttonPressed{};

class InputDispatcher
{
public:
    static void rotate(int offset)
    {
        rotated += offset;
    }

    static void button(bool pressed)
    {
        static unsigned long pressBegin = 0;

        const auto now = millis();

        if (pressed)
            pressBegin = now;
        else
        {
            const auto duration = now - pressBegin;

            if (duration < 1000)
                buttonPressed = true;
            else if (duration < 3000)
                buttonLongPressed = true;
            else
                requestFullRedraw = true;

            pressBegin = 0;
        }
    }
};
}
