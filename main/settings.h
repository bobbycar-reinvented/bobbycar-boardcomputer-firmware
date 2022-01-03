#pragma once

// system includes
#include <cstdint>
#include <array>
#include <FastLED.h>

// esp-idf includes
#include <esp_wifi_types.h>
#ifdef FEATURE_NTP
#include <lwip/apps/snmp.h>
#include <esp_sntp.h>
#endif

// 3rdparty lib includes
#include <espchrono.h>

// local includes
#include "bobbycar-common.h"
#include "unifiedmodelmode.h"
#include "modes/larsmmode.h"

struct Settings
{
    struct Limits {
        int16_t iMotMax;      // [A] Maximum motor current limit // profileSetting
        int16_t iDcMax;       // [A] Maximum DC Link current limit (This is the current protection. Above this value, current chopping is applied. To avoid this make sure that I_DC_MAX = I_MOT_MAX + 2A) // profileSetting
        int16_t nMotMax;      // [rpm] Maximum motor speed limit // profileSetting
        int16_t fieldWeakMax; // [A] Maximum Field Weakening D axis current (only for FOC). Higher current results in higher maximum speed. // profileSetting
        int16_t phaseAdvMax;  // [deg] Maximum Phase Advance angle (only for SIN). Higher angle results in higher maximum speed. // profileSetting
    } limits;

    struct ControllerHardware {
        bool enableFrontLeft, enableFrontRight, enableBackLeft, enableBackRight; // profileSetting
        bool invertFrontLeft, invertFrontRight, invertBackLeft, invertBackRight; // profileSetting
    } controllerHardware;

    struct DefaultMode {
        UnifiedModelMode modelMode;        // profileSetting
        bool squareGas;                    // profileSetting
        bool squareBrems;                  // profileSetting
        bool enableSmoothingUp;            // profileSetting
        bool enableSmoothingDown;          // profileSetting
        bool enableFieldWeakSmoothingUp;   // profileSetting
        bool enableFieldWeakSmoothingDown; // profileSetting
        int16_t smoothing;                 // profileSetting
        int16_t frontPercentage;           // profileSetting
        int16_t backPercentage;            // profileSetting
        int16_t add_schwelle;              // profileSetting
        int16_t gas1_wert;                 // profileSetting
        int16_t gas2_wert;                 // profileSetting
        int16_t brems1_wert;               // profileSetting
        int16_t brems2_wert;               // profileSetting
        int16_t fwSmoothLowerLimit;        // profileSetting
    } defaultMode;

    struct TempomatMode {
        UnifiedModelMode modelMode; // profileSetting
    } tempomatMode;

    struct LarsmMode {
        UnifiedModelMode modelMode; // profileSetting
        LarsmModeMode mode;         // profileSetting
        uint8_t iterations;         // profileSetting
    } larsmMode;

    struct MotortestMode {
        uint8_t multiplikator;      // profileSetting
        uint16_t maxPwm;            // profileSetting
    } motortestMode;

    template<typename T>
    void executeForEveryCommonSetting(T &&callable);

    template<typename T>
    void executeForEveryProfileSetting(T &&callable);
};

template<typename T>
void Settings::executeForEveryCommonSetting(T &&callable)
{
}

template<typename T>
void Settings::executeForEveryProfileSetting(T &&callable)
{
    callable("iMotMax", limits.iMotMax);
    callable("iDcMax", limits.iDcMax);
    callable("nMotMax", limits.nMotMax);
    callable("fieldWeakMax", limits.fieldWeakMax);
    callable("phaseAdvMax", limits.phaseAdvMax);

    callable("enableFrontLeft", controllerHardware.enableFrontLeft);
    callable("enableFrontRigh", controllerHardware.enableFrontRight);
    callable("enableBackLeft", controllerHardware.enableBackLeft);
    callable("enableBackRight", controllerHardware.enableBackRight);

    callable("invertFrontLeft", controllerHardware.invertFrontLeft);
    callable("invertFrontRigh", controllerHardware.invertFrontRight);
    callable("invertBackLeft", controllerHardware.invertBackLeft);
    callable("invertBackRight", controllerHardware.invertBackRight);

    callable("default.modelMo", defaultMode.modelMode);
    callable("default.enSmUp_", defaultMode.enableSmoothingUp);
    callable("default.enSmDow", defaultMode.enableSmoothingDown);
    callable("default.enSmFUp", defaultMode.enableFieldWeakSmoothingUp);
    callable("default.enSmFDo", defaultMode.enableFieldWeakSmoothingDown);
    callable("default.fwSmLLi", defaultMode.fwSmoothLowerLimit);
    callable("default.smoothi", defaultMode.smoothing);
    callable("default.frontPe", defaultMode.frontPercentage);
    callable("default.backPer", defaultMode.backPercentage);
    callable("default.add_sch", defaultMode.add_schwelle);
    callable("default.gas1_we", defaultMode.gas1_wert);
    callable("default.gas2_we", defaultMode.gas2_wert);
    callable("default.brems1_", defaultMode.brems1_wert);
    callable("default.brems2_", defaultMode.brems2_wert);
    callable("default.squareG", defaultMode.squareGas);
    callable("default.squareB", defaultMode.squareBrems);

    callable("tempoma.modelMo", tempomatMode.modelMode);

    callable("larsm.modelMode", larsmMode.modelMode);
    callable("larsm.mode", larsmMode.mode);
    callable("larsm.iters", larsmMode.iterations);
}
