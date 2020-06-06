#pragma once

#include <HardwareSerial.h>
#include <WiFi.h>

#include "actioninterface.h"
#include "globals.h"

namespace {
class WifiSoftApAction : public virtual ActionInterface
{
public:
    void triggered() override
    {
        if (!WiFi.softAP(deviceName, "Passwort_123"))
        {
            Serial.println("Could not softAP WiFi");
            // TODO: better error handling
        }
    }
};
}
