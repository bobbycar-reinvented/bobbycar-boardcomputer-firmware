#include "controller.h"

// local includes
#include "globals.h"

Controller::Controller(
#ifdef FEATURE_SERIAL
    HardwareSerial &serial,
#endif
    bool &enableLeft, bool &enableRight, bool &invertLeft, bool &invertRight,
    espconfig::ConfigWrapper<int16_t> &voltageCalib30V, espconfig::ConfigWrapper<int16_t> &voltageCalib50V
) :
    #ifdef FEATURE_SERIAL
    serial{serial},
    #endif
    enableLeft{enableLeft}, enableRight{enableRight}, invertLeft{invertLeft}, invertRight{invertRight},
    voltageCalib30V{voltageCalib30V}, voltageCalib50V{voltageCalib50V}
{
}

float Controller::getCalibratedVoltage() const
{
    float voltage = feedback.batVoltage;
    if (configs.battery.applyCalibration.value)
    {
        voltage = ((voltage - float(voltageCalib30V.value)) * (20.f / (float(voltageCalib50V.value) - float(voltageCalib30V.value))) + 30.f);
    }
    else
    {
        voltage = voltage / 100.;
    }
    return voltage;
}
