#pragma once

#include <cstdint>

#include <Arduino.h>

#include "modeinterface.h"
#include "globals.h"
#include "utils.h"
#include "types.h"

namespace {
class DefaultMode : public ModeInterface
{
public:
    void update() override;

    const char *displayName() const override { return "Default"; }

    bool waitForGasLoslass{false};
    bool waitForBremsLoslass{false};

private:
    millis_t lastTime{millis()};
    float lastPwm{0};
};

namespace modes {
DefaultMode defaultMode;
}

void DefaultMode::update()
{
    if (waitForGasLoslass)
    {
        if (gas < 50)
            waitForGasLoslass = false;
        else
            gas = 0;
    }

    if (waitForBremsLoslass)
    {
        if (brems < 50)
            waitForBremsLoslass = false;
        else
            brems = 0;
    }

    const auto gas_processed = settings.defaultMode.squareGas ? (gas * gas) / 1000.f : gas;
    const auto brems_processed = settings.defaultMode.squareBrems ? (brems * brems) / 1000 : brems;

    const auto now = millis();

    float pwm;
    if (gas_processed >= settings.defaultMode.add_schwelle)
    {
        pwm = (gas_processed/1000.*settings.defaultMode.gas1_wert) + (brems_processed/1000.*settings.defaultMode.brems1_wert);

        if (settings.defaultMode.enableSmoothing && (pwm > 1000. || lastPwm > 1000.))
        {
            if (lastPwm < pwm)
            {
                pwm = std::min(pwm, lastPwm+(settings.defaultMode.smoothing*(now-lastTime)/100.f));
                if (pwm < 1000.)
                    pwm = 1000.;
            }
            else if (lastPwm > pwm)
            {
                pwm = std::max(pwm, lastPwm-(settings.defaultMode.smoothing*(now-lastTime)/100.f));
            }
        }
    }
    else
        pwm = (gas_processed/1000.*settings.defaultMode.gas2_wert) - (brems_processed/1000.*settings.defaultMode.brems2_wert);

    lastPwm = pwm;
    lastTime = now;

    const auto pair = split(settings.defaultMode.modelMode);
    for (bobbycar::protocol::serial::MotorState &motor : motorsInController(controllers.front))
    {
        motor.ctrlTyp = pair.first;
        motor.ctrlMod = pair.second;
        motor.pwm = pwm / 100. * settings.defaultMode.frontPercentage;
    }
    for (bobbycar::protocol::serial::MotorState &motor : motorsInController(controllers.back))
    {
        motor.ctrlTyp = pair.first;
        motor.ctrlMod = pair.second;
        motor.pwm = pwm / 100. * settings.defaultMode.backPercentage;
    }

    fixCommonParams();

    sendCommands();
}
}
