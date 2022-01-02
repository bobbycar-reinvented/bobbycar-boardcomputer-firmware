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
#include "handbremse.h"
#include "ledstrip.h"
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

    struct BoardcomputerHardware {
#ifdef FEATURE_GAMETRAK
        int16_t gametrakXMin, gametrakXMax, gametrakYMin, gametrakYMax, gametrakDistMin, gametrakDistMax;
#endif

        struct TimersSettings {
            int16_t statsUpdateRate;
#ifdef FEATURE_CLOUD
            int16_t cloudCollectRate;
            int16_t cloudSendRate;
#endif
#ifdef FEATURE_UDPCLOUD
            int16_t udpSendRateMs;
#endif
        } timersSettings;
    } boardcomputerHardware;

#ifdef FEATURE_CLOUD
    struct CloudSettings {
        bool cloudEnabled;
        int16_t cloudTransmitTimeout; // in ms
    } cloudSettings;
#endif

#ifdef FEATURE_UDPCLOUD
    struct UdpCloudSettings {
        uint32_t udpUid;
        bool udpCloudEnabled;
        bool enableCloudDebug;
        bool udpUseStdString;
    } udpCloudSettings;
#endif

    struct DefaultMode {
        UnifiedModelMode modelMode;        // profileSetting
        bool squareGas;
        bool squareBrems;
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
        uint8_t multiplikator;
        uint16_t maxPwm;
    } motortestMode;

#ifdef FEATURE_LEDSTRIP
    struct Ledstrip {
        bool enableLedAnimation;
        bool enableBrakeLights;
        int16_t ledsCount;
        int16_t centerOffset;
        int16_t smallOffset;
        int16_t bigOffset;
        bool enableBeepWhenBlink;
        int16_t animationType;
        bool enableFullBlink;
        bool enableStVO;
        int16_t stvoFrontOffset;
        int16_t stvoFrontLength;
        bool stvoFrontEnable;
        int16_t animationMultiplier;
        uint8_t brightness;
        bool enableAnimBlink;
#ifdef FEATURE_OTA
        OtaAnimationModes otaMode;
#endif
    } ledstrip;
#endif

    struct Battery {
        uint8_t cellsSeries;
        uint8_t cellsParallel;
        uint8_t cellType;
        uint16_t watthoursPerKilometer;
        int16_t front30VoltCalibration;
        int16_t back30VoltCalibration;
        int16_t front50VoltCalibration;
        int16_t back50VoltCalibration;
        bool applyCalibration;
    } battery;

    struct Hybrid {
        UnifiedModelMode hybridMode;
        bool enable;
        int16_t activationLimit;
        int16_t deactivationLimit;
    } hybrid;

    struct LockscreenSettings {
        bool allowPresetSwitch;
        bool keepLockedAfterReboot;
        bool locked;
        std::array<int8_t, 4> pin;
    } lockscreen;

    struct SavedStatistics {
        uint32_t totalCentimeters;
    } savedStatistics;

    struct Handbremse {
        HandbremseMode mode;
        uint16_t triggerTimeout;
        bool automatic;
        bool enable;
        bool visualize;
    } handbremse;
#ifdef FEATURE_ESPNOW
    struct ESPNOW {
        bool syncTime;
        bool syncTimeWithOthers;
        bool syncBlink;
    } espnow;
#endif

    template<typename T>
    void executeForEveryCommonSetting(T &&callable);

    template<typename T>
    void executeForEveryProfileSetting(T &&callable);
};

template<typename T>
void Settings::executeForEveryCommonSetting(T &&callable)
{
#ifdef FEATURE_GAMETRAK
    callable("gametrakXMin", boardcomputerHardware.gametrakXMin);
    callable("gametrakXMax", boardcomputerHardware.gametrakXMax);
    callable("gametrakYMin", boardcomputerHardware.gametrakYMin);
    callable("gametrakYMax", boardcomputerHardware.gametrakYMax);
    callable("gametrakDistMin", boardcomputerHardware.gametrakDistMin);
    callable("gametrakDistMax", boardcomputerHardware.gametrakDistMax);
#endif

    callable("statsUpdateRate", boardcomputerHardware.timersSettings.statsUpdateRate);
#ifdef FEATURE_CLOUD
    callable("cloudCollectRat", boardcomputerHardware.timersSettings.cloudCollectRate);
    callable("cloudSendRate", boardcomputerHardware.timersSettings.cloudSendRate);
#endif
#ifdef FEATURE_UDPCLOUD
    callable("udpSendRate", boardcomputerHardware.timersSettings.udpSendRateMs);
#endif

#ifdef FEATURE_CLOUD
    callable("cloudEnabled", cloudSettings.cloudEnabled);
    callable("clodTransmTmout", cloudSettings.cloudTransmitTimeout);
#endif

#ifdef FEATURE_UDPCLOUD
    callable("cloudUDPUid", udpCloudSettings.udpUid);
    callable("enUdpCloud", udpCloudSettings.udpCloudEnabled);
    callable("debugCloud", udpCloudSettings.enableCloudDebug);
    callable("udpusestdstr", udpCloudSettings.udpUseStdString);
#endif

#ifdef FEATURE_LEDSTRIP
    callable("enableLedAnimat", ledstrip.enableLedAnimation);
    callable("enableBrakeLigh", ledstrip.enableBrakeLights);
    callable("ledsCount", ledstrip.ledsCount);
    callable("centerOffset", ledstrip.centerOffset);
    callable("smallOffset", ledstrip.smallOffset);
    callable("bigOffset", ledstrip.bigOffset);
    callable("beeppwhenblink", ledstrip.enableBeepWhenBlink);
//    callable("animationType", ledstrip.animationType);
    callable("fullblink", ledstrip.enableFullBlink);
    callable("ledstvo", ledstrip.enableStVO);
    callable("ledstvofoff", ledstrip.stvoFrontOffset);
    callable("ledstvoflen", ledstrip.stvoFrontLength);
    callable("ledstvoen", ledstrip.stvoFrontEnable);
    callable("ledAnimMul", ledstrip.animationMultiplier);
    callable("ledbrightness", ledstrip.brightness);
    callable("enAnimBlink", ledstrip.enableAnimBlink);
#ifdef FEATURE_OTA
    callable("ledOtaAnim", ledstrip.otaMode);
#endif
#endif

    callable("batteryCS", battery.cellsSeries);
    callable("batteryCP", battery.cellsParallel);
    callable("batteryType", battery.cellType);
    callable("whkm", battery.watthoursPerKilometer);
    callable("batF30VCal", battery.front30VoltCalibration);
    callable("batB30VCal", battery.back30VoltCalibration);
    callable("batF50VCal", battery.front50VoltCalibration);
    callable("batB50VCal", battery.back50VoltCalibration);
    callable("applyBatCal", battery.applyCalibration);

    callable("hybridMode", hybrid.hybridMode);
    callable("hybridEn", hybrid.enable);
    callable("hybridAcL", hybrid.activationLimit);
    callable("hybridDeacL", hybrid.deactivationLimit);

    callable("lockAlwPresetSw", lockscreen.allowPresetSwitch);
    callable("keepLocked", lockscreen.keepLockedAfterReboot);
    callable("currentlyLocked", lockscreen.locked);
    callable("lockscreenPin", lockscreen.pin);

    callable("totalCentimeter", savedStatistics.totalCentimeters);

    callable("handBremsE", handbremse.enable);
    callable("handBremsA", handbremse.automatic);
    callable("handBremsM", handbremse.mode);
    callable("handBremsT", handbremse.triggerTimeout);
    callable("handBremsV", handbremse.visualize);

#ifdef FEATURE_ESPNOW
    callable("espnowSyncT", espnow.syncTime);
    callable("espnowSyncTWO", espnow.syncTimeWithOthers);
#ifdef FEATURE_LEDSTRIP
    callable("espnowSyncBl", espnow.syncBlink);
#endif
#endif
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

    callable("tempoma.modelMo", tempomatMode.modelMode);

    callable("larsm.modelMode", larsmMode.modelMode);
    callable("larsm.mode", larsmMode.mode);
    callable("larsm.iters", larsmMode.iterations);
}
