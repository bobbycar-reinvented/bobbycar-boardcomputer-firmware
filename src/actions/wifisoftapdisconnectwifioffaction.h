#pragma once

#include <HardwareSerial.h>
#include <WiFi.h>

#include "actioninterface.h"

namespace {
class WifiSoftApDisconnectWifioffAction : public virtual ActionInterface
{
public:
    void triggered() override
    {
        if (!WiFi.softAPdisconnect(true))
        {
            Serial.println("Could not softAPdisconnect wifioff WiFi");
            // TODO: better error handling
        }
    }
};
}
