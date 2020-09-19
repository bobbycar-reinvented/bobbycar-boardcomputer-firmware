#pragma once

#include <HardwareSerial.h>

#include "actioninterface.h"
#include "globals.h"

namespace {
template<uint8_t profile>
class SwitchProfileAction : public virtual ActionInterface
{
public:
    void triggered() override
    {
        if (settingsPersister.openProfile(profile))
        {
            if (!settingsPersister.load(settings))
                Serial.println("SwitchProfileAction::triggered() load failed");
        }
        else
            Serial.println("SwitchProfileAction::triggered() openProfile failed");
    }
};
}
