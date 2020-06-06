#pragma once

#include <HardwareSerial.h>
#include <WiFi.h>

#include "actioninterface.h"

namespace {
class WifiSoftApDisconnectAction : public virtual ActionInterface
{
public:
    void triggered() override
    {
        if (!WiFi.softAPdisconnect())
        {
            Serial.println("Could not softAPdisconnect WiFi");
            // TODO: better error handling
        }
    }
};
}
