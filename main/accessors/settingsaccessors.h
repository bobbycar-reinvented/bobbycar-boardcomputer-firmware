#pragma once

// 3rdparty lib includes
#include <accessorinterface.h>

// local includes
#include "globals.h"
#include "utils.h"
#include "accessorhelpers.h"
#include "newsettings.h"

// Bluetooth
struct BluetoothNameAccessor : public NewSettingsAccessor<std::string> { ConfigWrapper<std::string> &getConfig() const override { return configs.bluetoothName; } };

// Buzzer
struct ReverseBeepAccessor : public NewSettingsAccessor<bool> { ConfigWrapper<bool> &getConfig() const override { return configs.reverseBeep; } };
struct ReverseBeepFreq0Accessor : public NewSettingsAccessor<uint8_t> { ConfigWrapper<uint8_t> &getConfig() const override { return configs.reverseBeepFreq0; } };
struct ReverseBeepFreq1Accessor : public NewSettingsAccessor<uint8_t> { ConfigWrapper<uint8_t> &getConfig() const override { return configs.reverseBeepFreq1; } };
struct ReverseBeepDuration0Accessor : public NewSettingsAccessor<int16_t> { ConfigWrapper<int16_t> &getConfig() const override { return configs.reverseBeepDuration0; } };
struct ReverseBeepDuration1Accessor : public NewSettingsAccessor<int16_t> { ConfigWrapper<int16_t> &getConfig() const override { return configs.reverseBeepDuration1; } };

// Limits
struct IMotMaxAccessor : public RefAccessorSaveSettings<int16_t> { int16_t &getRef() const override { return settings.limits.iMotMax; } };
struct IDcMaxAccessor : public RefAccessorSaveSettings<int16_t> { int16_t &getRef() const override { return settings.limits.iDcMax; } };
struct NMotMaxKmhAccessor : public virtual espgui::AccessorInterface<int16_t>
{
    int16_t getValue() const override { return convertToKmh(settings.limits.nMotMax); }
    espgui::AccessorInterface<int16_t>::setter_result_t setValue(int16_t value) override
    {
        settings.limits.nMotMax = convertFromKmh(value);
        if (!saveSettings())
            return tl::make_unexpected("saveSettings() failed!");
        return {};
    }
};
struct NMotMaxRpmAccessor : public RefAccessorSaveSettings<int16_t> { int16_t &getRef() const override { return settings.limits.nMotMax; } };
struct FieldWeakMaxAccessor : public RefAccessorSaveSettings<int16_t> { int16_t &getRef() const override { return settings.limits.fieldWeakMax; } };
struct PhaseAdvMaxAccessor : public RefAccessorSaveSettings<int16_t> { int16_t &getRef() const override { return settings.limits.phaseAdvMax; } };

// Bluetooth Low Energy
#ifdef FEATURE_BLE
struct BleEnabledAccessor : public NewSettingsAccessor<bool> { ConfigWrapper<bool> &getConfig() const override { return configs.bleSettings.bleEnabled; } };
#endif

// Cloud
#ifdef FEATURE_CLOUD
struct CloudEnabledAccessor : public NewSettingsAccessor<bool> { ConfigWrapper<bool> &getConfig() const override { return configs.cloudSettings.cloudEnabled; } };
struct CloudTransmitTimeoutAccessor : public NewSettingsAccessor<int16_t> { ConfigWrapper<int16_t> &getConfig() const override { return configs.cloudSettings.cloudTransmitTimeout; } };
#endif

// Time
//struct TimezoneOffsetAccessor : public NewSettingsAccessor<int32_t> { ConfigWrapper<int32_t> &getConfig() const override { return configs.timezoneOffset; } };
struct TimezoneOffsetAccessor : public NewSettingsChronoAdaptorAccessor<espchrono::minutes32> { ConfigWrapper<espchrono::minutes32> &getConfig() const override { return configs.timezoneOffset; } };
struct DaylightSavingModeAccessor : public NewSettingsAccessor<espchrono::DayLightSavingMode> { ConfigWrapper<espchrono::DayLightSavingMode> &getConfig() const override { return configs.timeDst; } };
#ifdef FEATURE_NTP
struct TimeServerEnabledAccessor : public NewSettingsAccessor<bool> { ConfigWrapper<bool> &getConfig() const override { return configs.timeServerEnabled; } };
struct TimeServerAccessor : public NewSettingsAccessor<std::string> { ConfigWrapper<std::string> &getConfig() const override { return configs.timeServer; } };
struct TimeSyncModeAccessor : public NewSettingsAccessor<sntp_sync_mode_t> { ConfigWrapper<sntp_sync_mode_t> &getConfig() const override { return configs.timeSyncMode; } };
//struct TimeSyncIntervalAccessor : public NewSettingsAccessor<int32_t> { ConfigWrapper<int32_t> &getConfig() const override { return configs.timeSyncInterval; } };
struct TimeSyncIntervalAccessor : public NewSettingsChronoAdaptorAccessor<espchrono::milliseconds32> { ConfigWrapper<espchrono::milliseconds32> &getConfig() const override { return configs.timeSyncInterval; } };
#endif

// Controller Hardware
struct FrontLeftEnabledAccessor : public RefAccessorSaveSettings<bool> { bool &getRef() const override { return settings.controllerHardware.enableFrontLeft; } };
struct FrontRightEnabledAccessor : public RefAccessorSaveSettings<bool> { bool &getRef() const override { return settings.controllerHardware.enableFrontRight; } };
struct BackLeftEnabledAccessor : public RefAccessorSaveSettings<bool> { bool &getRef() const override { return settings.controllerHardware.enableBackLeft; } };
struct BackRightEnabledAccessor : public RefAccessorSaveSettings<bool> { bool &getRef() const override { return settings.controllerHardware.enableBackRight; } };

struct FrontLeftInvertedAccessor : public RefAccessorSaveSettings<bool> { bool &getRef() const override { return settings.controllerHardware.invertFrontLeft; } };
struct FrontRightInvertedAccessor : public RefAccessorSaveSettings<bool> { bool &getRef() const override { return settings.controllerHardware.invertFrontRight; } };
struct BackLeftInvertedAccessor : public RefAccessorSaveSettings<bool> { bool &getRef() const override { return settings.controllerHardware.invertBackLeft; } };
struct BackRightInvertedAccessor : public RefAccessorSaveSettings<bool> { bool &getRef() const override { return settings.controllerHardware.invertBackRight; } };

struct WheelDiameterMmAccessor : public NewSettingsAccessor<int16_t> { ConfigWrapper<int16_t> &getConfig() const override { return configs.controllerHardware.wheelDiameter; } };
struct WheelDiameterInchAccessor : public virtual espgui::AccessorInterface<float>
{
    float getValue() const override { return convertToInch(configs.controllerHardware.wheelDiameter.value); }
    espgui::AccessorInterface<int16_t>::setter_result_t setValue(float value) override
    {
//        settings.controllerHardware.wheelDiameter = convertFromInch(value);
//        if (!saveSettings())
//            return tl::make_unexpected("saveSettings() failed!");
//        return {};
        return configs.write_config(configs.controllerHardware.wheelDiameter, convertFromInch(value));
    }
};
struct NumMagnetPolesAccessor : public NewSettingsAccessor<int16_t> { ConfigWrapper<int16_t> &getConfig() const override { return configs.controllerHardware.numMagnetPoles; } };
struct SwapFrontBackAccessor : public virtual espgui::AccessorInterface<bool> {
    bool getValue() const override { return configs.controllerHardware.swapFrontBack.value; }
    setter_result_t setValue(bool value) override
    {
        const auto err = configs.write_config(configs.controllerHardware.swapFrontBack, value);
#ifdef FEATURE_SERIAL
        updateSwapFrontBack();
#endif
        return err;
    }
};

// CAN
#ifdef FEATURE_CAN
struct SendFrontCanCmdAccessor : public NewSettingsAccessor<bool> { ConfigWrapper<bool> &getConfig() const override { return configs.controllerHardware.sendFrontCanCmd; } };
struct SendBackCanCmdAccessor : public NewSettingsAccessor<bool> { ConfigWrapper<bool> &getConfig() const override { return configs.controllerHardware.sendBackCanCmd; } };
struct CanTransmitTimeoutAccessor : public NewSettingsAccessor<int16_t> { ConfigWrapper<int16_t> &getConfig() const override { return configs.controllerHardware.canTransmitTimeout; } };
struct CanReceiveTimeoutAccessor : public NewSettingsAccessor<int16_t> { ConfigWrapper<int16_t> &getConfig() const override { return configs.controllerHardware.canReceiveTimeout; } };
#endif

// Input devices
struct SampleCountAccessor : public NewSettingsAccessor<int16_t> { ConfigWrapper<int16_t> &getConfig() const override { return configs.sampleCount; } };
struct GasMinAccessor : public NewSettingsAccessor<int16_t> { ConfigWrapper<int16_t> &getConfig() const override { return configs.gasMin; } };
struct GasMaxAccessor : public NewSettingsAccessor<int16_t> { ConfigWrapper<int16_t> &getConfig() const override { return configs.gasMax; } };
struct BremsMinAccessor : public NewSettingsAccessor<int16_t> { ConfigWrapper<int16_t> &getConfig() const override { return configs.bremsMin; } };
struct BremsMaxAccessor : public NewSettingsAccessor<int16_t> { ConfigWrapper<int16_t> &getConfig() const override { return configs.bremsMax; } };
#if defined(FEATURE_DPAD) || defined(FEATURE_DPAD_3WIRESW) || defined(FEATURE_DPAD_5WIRESW) || defined(FEATURE_DPAD_5WIRESW_2OUT) || defined (FEATURE_DPAD_6WIRESW)
struct DPadDebounceAccessor : public NewSettingsAccessor<uint8_t> { ConfigWrapper<uint8_t> &getConfig() const override { return configs.dpadDebounce; } };
#endif
#ifdef FEATURE_GAMETRAK
struct GametrakXMinAccessor : public NewSettingsAccessor<int16_t> { ConfigWrapper<int16_t> &getConfig() const override { return configs.boardcomputerHardware.gametrakXMin; } };
struct GametrakXMaxAccessor : public NewSettingsAccessor<int16_t> { ConfigWrapper<int16_t> &getConfig() const override { return configs.boardcomputerHardware.gametrakXMax; } };
struct GametrakYMinAccessor : public NewSettingsAccessor<int16_t> { ConfigWrapper<int16_t> &getConfig() const override { return configs.boardcomputerHardware.gametrakYMin; } };
struct GametrakYMaxAccessor : public NewSettingsAccessor<int16_t> { ConfigWrapper<int16_t> &getConfig() const override { return configs.boardcomputerHardware.gametrakYMax; } };
struct GametrakDistMinAccessor : public NewSettingsAccessor<int16_t> { ConfigWrapper<int16_t> &getConfig() const override { return configs.boardcomputerHardware.gametrakDistMin; } };
struct GametrakDistMaxAccessor : public NewSettingsAccessor<int16_t> { ConfigWrapper<int16_t> &getConfig() const override { return configs.boardcomputerHardware.gametrakDistMax; } };
#endif
struct StatsUpdateRateAccessor : public NewSettingsAccessor<int16_t> { ConfigWrapper<int16_t> &getConfig() const override { return configs.boardcomputerHardware.timersSettings.statsUpdateRate; } };

// Cloud
#ifdef FEATURE_CLOUD
struct CloudCollectRateAccessor : public NewSettingsAccessor<int16_t> { ConfigWrapper<int16_t> &getConfig() const override { return configs.boardcomputerHardware.timersSettings.cloudCollectRate; } };
struct CloudSendRateAccessor : public NewSettingsAccessor<int16_t> { ConfigWrapper<int16_t> &getConfig() const override { return configs.boardcomputerHardware.timersSettings.cloudSendRate; } };
#endif

#ifdef FEATURE_UDPCLOUD
struct UdpCloudSendIntervalAccessor : public NewSettingsAccessor<int16_t> { ConfigWrapper<int16_t> &getConfig() const override { return configs.boardcomputerHardware.timersSettings.udpSendRateMs; } };
struct UdpCloudEnabledAccessor : public NewSettingsAccessor<bool> { ConfigWrapper<bool> &getConfig() const override { return configs.udpCloudSettings.udpCloudEnabled; } };
struct CloudDebugEnableAccessor : public NewSettingsAccessor<bool> { ConfigWrapper<bool> &getConfig() const override { return configs.udpCloudSettings.enableCloudDebug; } };
struct UdpUseStdStringAccessor : public NewSettingsAccessor<bool> { ConfigWrapper<bool> &getConfig() const override { return configs.udpCloudSettings.udpUseStdString; } };
#endif

// DefaultMode
struct DefaultModeModelModeAccessor : public RefAccessorSaveSettings<UnifiedModelMode> { UnifiedModelMode &getRef() const override { return settings.defaultMode.modelMode; } };
struct DefaultModeHybridModelModeAccessor : public RefAccessorSaveSettings<UnifiedModelMode> { UnifiedModelMode &getRef() const override { return settings.hybrid.hybridMode; } };
struct DefaultModeSquareGasAccessor : public RefAccessorSaveSettings<bool> { bool &getRef() const override { return settings.defaultMode.squareGas; } };
struct DefaultModeSquareBremsAccessor : public RefAccessorSaveSettings<bool> { bool &getRef() const override { return settings.defaultMode.squareBrems; } };

struct DefaultModeEnableSmoothingUpAccessor : public RefAccessorSaveSettings<bool> { bool &getRef() const override { return settings.defaultMode.enableSmoothingUp; } };
struct DefaultModeEnableSmoothingDownAccessor : public RefAccessorSaveSettings<bool> { bool &getRef() const override { return settings.defaultMode.enableSmoothingDown; } };
struct DefaultModeEnableFieldWeakSmoothingUpAccessor : public RefAccessorSaveSettings<bool> { bool &getRef() const override { return settings.defaultMode.enableFieldWeakSmoothingUp; } };
struct DefaultModeEnableFieldWeakSmoothingDownAccessor : public RefAccessorSaveSettings<bool> { bool &getRef() const override { return settings.defaultMode.enableFieldWeakSmoothingDown; } };
struct DefaultModeEnableFieldWeakSmoothingLowerLimitAccessor : public RefAccessorSaveSettings<int16_t> { int16_t &getRef() const override { return settings.defaultMode.fwSmoothLowerLimit; } };

struct DefaultModeSmoothingAccessor : public RefAccessorSaveSettings<int16_t> { int16_t &getRef() const override { return settings.defaultMode.smoothing; } };
struct DefaultModeFrontPercentageAccessor : public RefAccessorSaveSettings<int16_t> { int16_t &getRef() const override { return settings.defaultMode.frontPercentage; } };
struct DefaultModeBackPercentageAccessor : public RefAccessorSaveSettings<int16_t> { int16_t &getRef() const override { return settings.defaultMode.backPercentage; } };
struct DefaultModeAddSchwelleAccessor : public RefAccessorSaveSettings<int16_t> { int16_t &getRef() const override { return settings.defaultMode.add_schwelle; } };
struct DefaultModeGas1WertAccessor : public RefAccessorSaveSettings<int16_t> { int16_t &getRef() const override { return settings.defaultMode.gas1_wert; } };
struct DefaultModeGas2WertAccessor : public RefAccessorSaveSettings<int16_t> { int16_t &getRef() const override { return settings.defaultMode.gas2_wert; } };
struct DefaultModeBrems1WertAccessor : public RefAccessorSaveSettings<int16_t> { int16_t &getRef() const override { return settings.defaultMode.brems1_wert; } };
struct DefaultModeBrems2WertAccessor : public RefAccessorSaveSettings<int16_t> { int16_t &getRef() const override { return settings.defaultMode.brems2_wert; } };

struct DefaultModeEnableHybridAccessor : public RefAccessorSaveSettings<bool> { bool &getRef() const override { return settings.hybrid.enable; } };
struct DefaultModeHybridActivationLimitAccessor : public RefAccessorSaveSettings<int16_t> { int16_t &getRef() const override { return settings.hybrid.activationLimit; } };
struct DefaultModeHybridDeactivationLimitAccessor : public RefAccessorSaveSettings<int16_t> { int16_t &getRef() const override { return settings.hybrid.deactivationLimit; } };

// TempomatMode
struct TempomatModeModelModeAccessor : public RefAccessorSaveSettings<UnifiedModelMode> { UnifiedModelMode &getRef() const override { return settings.tempomatMode.modelMode; } };

// LarsmMode
struct LarsmModeModelModeAccessor : public RefAccessorSaveSettings<UnifiedModelMode> { UnifiedModelMode &getRef() const override { return settings.larsmMode.modelMode; } };
struct LarsmModeModeAccessor : public RefAccessorSaveSettings<LarsmModeMode> { LarsmModeMode &getRef() const override { return settings.larsmMode.mode; } };
struct LarsmModeIterationsAccessor : public RefAccessorSaveSettings<uint8_t> { uint8_t &getRef() const override { return settings.larsmMode.iterations; } };

// MotortestMode
struct MotortestModeMultiplikatorAccessor : public RefAccessorSaveSettings<uint8_t> { uint8_t &getRef() const override { return settings.motortestMode.multiplikator; } };
struct MotortestMaxPwmAccessor : public RefAccessorSaveSettings<uint16_t> { uint16_t &getRef() const override { return settings.motortestMode.maxPwm; } };

// Ledstrip
#ifdef FEATURE_LEDSTRIP
struct EnableLedAnimationAccessor : public NewSettingsAccessor<bool> { ConfigWrapper<bool> &getConfig() const override { return configs.ledstrip.enableLedAnimation; } };
struct EnableBrakeLightsAccessor : public NewSettingsAccessor<bool> { ConfigWrapper<bool> &getConfig() const override { return configs.ledstrip.enableBrakeLights; } };
struct LedsCountAccessor : public NewSettingsAccessor<int16_t> { ConfigWrapper<int16_t> &getConfig() const override { return configs.ledstrip.ledsCount; } };
struct CenterOffsetAccessor : public NewSettingsAccessor<int16_t> { ConfigWrapper<int16_t> &getConfig() const override { return configs.ledstrip.centerOffset; } };
struct SmallOffsetAccessor : public NewSettingsAccessor<int16_t> { ConfigWrapper<int16_t> &getConfig() const override { return configs.ledstrip.smallOffset; } };
struct BigOffsetAccessor : public NewSettingsAccessor<int16_t> { ConfigWrapper<int16_t> &getConfig() const override { return configs.ledstrip.bigOffset; } };
struct LedStripMaxMilliampsAccessor : public NewSettingsAccessor<uint32_t> { ConfigWrapper<uint32_t> &getConfig() const override { return configs.ledstrip.maxMilliamps; } };
struct LedStripMaxAmpereAccessor : public virtual espgui::AccessorInterface<float>
{
    float getValue() const override
    {
        return configs.ledstrip.maxMilliamps.value / 1000.f;
    }

    espgui::AccessorInterface<float>::setter_result_t setValue(float value) override
    {
        return configs.write_config(configs.ledstrip.maxMilliamps, value * 1000);
    }
};
struct EnableBeepWhenBlinkAccessor : public NewSettingsAccessor<bool> { ConfigWrapper<bool> &getConfig() const override { return configs.ledstrip.enableBeepWhenBlink; } };
struct EnableFullBlinkAccessor : public NewSettingsAccessor<bool> { ConfigWrapper<bool> &getConfig() const override { return configs.ledstrip.enableFullBlink; } };
struct EnableLedstripStVOAccessor : public NewSettingsAccessor<bool> { ConfigWrapper<bool> &getConfig() const override { return configs.ledstrip.enableStVO; } };
struct LedsStVOFrontOffsetAccessor : public NewSettingsAccessor<int16_t> { ConfigWrapper<int16_t> &getConfig() const override { return configs.ledstrip.stvoFrontOffset; } };
struct LedsStVOFrontLengthAccessor : public NewSettingsAccessor<int16_t> { ConfigWrapper<int16_t> &getConfig() const override { return configs.ledstrip.stvoFrontLength; } };
struct EnableLedstripStVOFrontlight : public NewSettingsAccessor<bool> { ConfigWrapper<bool> &getConfig() const override { return configs.ledstrip.stvoFrontEnable; } };
struct AnimationMultiplierAccessor : public NewSettingsAccessor<int16_t> { ConfigWrapper<int16_t> &getConfig() const override { return configs.ledstrip.animationMultiplier; } };
struct LedstripBrightnessAccessor : public NewSettingsAccessor<uint8_t> { ConfigWrapper<uint8_t> &getConfig() const override { return configs.ledstrip.brightness; } };
struct LedstripEnableBlinkAnimationAccessor : public NewSettingsAccessor<bool> { ConfigWrapper<bool> &getConfig() const override { return configs.ledstrip.enableAnimBlink; } };
#ifdef FEATURE_OTA
struct LedstripOtaAnimationAccessor : public NewSettingsAccessor<OtaAnimationModes> { ConfigWrapper<OtaAnimationModes> &getConfig() const override { return configs.ledstrip.otaMode; } };
#endif
#endif

// Battery
struct BatterySeriesCellsAccessor : public NewSettingsAccessor<uint8_t> { ConfigWrapper<uint8_t> &getConfig() const override { return configs.battery.cellsSeries; } };
struct BatteryParallelCellsAccessor : public NewSettingsAccessor<uint8_t> { ConfigWrapper<uint8_t> &getConfig() const override { return configs.battery.cellsParallel; } };
struct BatteryWHperKMAccessor : public NewSettingsAccessor<uint16_t> { ConfigWrapper<uint16_t> &getConfig() const override { return configs.battery.watthoursPerKilometer; } };
struct BatteryApplyCalibrationAccessor : public NewSettingsAccessor<bool> { ConfigWrapper<bool> &getConfig() const override { return configs.battery.applyCalibration; } };

// Lockscreen
struct LockscreenAllowPresetSwitchAccessor : public RefAccessorSaveSettings<bool> { bool &getRef() const override { return settings.lockscreen.allowPresetSwitch; } };
template<uint8_t index>
struct LockscreenPinDigitAccessor : public RefAccessorSaveSettings<int8_t> { int8_t &getRef() const override { return settings.lockscreen.pin[index]; } };
struct LockscreenKeepLockedAccessor : public RefAccessorSaveSettings<bool> { bool &getRef() const override { return settings.lockscreen.keepLockedAfterReboot; } };

// Handbremse
struct HandbremsEnabledAccessor : public RefAccessorSaveSettings<bool> { bool &getRef() const override { return settings.handbremse.enable; } };
struct HandbremsModeAccessor : public RefAccessorSaveSettings<HandbremseMode> { HandbremseMode &getRef() const override { return settings.handbremse.mode; } };
struct HandbremsTimeoutAccessor : public RefAccessorSaveSettings<uint16_t> { uint16_t &getRef() const override { return settings.handbremse.triggerTimeout; } };
struct HandbremsAutomaticAccessor : public RefAccessorSaveSettings<bool> { bool &getRef() const override { return settings.handbremse.automatic; } };
struct HandbremsVisualizeAccessor : public RefAccessorSaveSettings<bool> { bool &getRef() const override { return settings.handbremse.visualize; } };

// ESP Now
#ifdef FEATURE_ESPNOW
struct ESPNowSyncTimeEnabledAccessor : public RefAccessorSaveSettings<bool> { bool &getRef() const override { return settings.espnow.syncTime; } };
struct ESPNowSyncTimeWithOthersEnabledAccessor : public RefAccessorSaveSettings<bool> { bool &getRef() const override { return settings.espnow.syncTimeWithOthers; } };
struct ESPNowSyncBlinkEnabledAccessor : public RefAccessorSaveSettings<bool> { bool &getRef() const override { return settings.espnow.syncBlink; } };
#endif

// Button Mapping accessors
struct ButtonLeftAccessor : public NewSettingsAccessor<uint8_t> { ConfigWrapper<uint8_t> &getConfig() const override { return configs.dpadMappingLeft; } };
struct ButtonRightAccessor : public NewSettingsAccessor<uint8_t> { ConfigWrapper<uint8_t> &getConfig() const override { return configs.dpadMappingRight; } };
struct ButtonUpAccessor : public NewSettingsAccessor<uint8_t> { ConfigWrapper<uint8_t> &getConfig() const override { return configs.dpadMappingUp; } };
struct ButtonDownAccessor : public NewSettingsAccessor<uint8_t> { ConfigWrapper<uint8_t> &getConfig() const override { return configs.dpadMappingDown; } };

struct ButtonLeft2Accessor : public NewSettingsAccessor<uint8_t> { ConfigWrapper<uint8_t> &getConfig() const override { return configs.dpadMappingLeft2; } };
struct ButtonRight2Accessor : public NewSettingsAccessor<uint8_t> { ConfigWrapper<uint8_t> &getConfig() const override { return configs.dpadMappingRight2; } };
struct ButtonUp2Accessor : public NewSettingsAccessor<uint8_t> { ConfigWrapper<uint8_t> &getConfig() const override { return configs.dpadMappingUp2; } };
struct ButtonDown2Accessor : public NewSettingsAccessor<uint8_t> { ConfigWrapper<uint8_t> &getConfig() const override { return configs.dpadMappingDown2; } };

struct ButtonProfile0Accessor : public NewSettingsAccessor<uint8_t> { ConfigWrapper<uint8_t> &getConfig() const override { return configs.dpadMappingProfile0; } };
struct ButtonProfile1Accessor : public NewSettingsAccessor<uint8_t> { ConfigWrapper<uint8_t> &getConfig() const override { return configs.dpadMappingProfile1; } };
struct ButtonProfile2Accessor : public NewSettingsAccessor<uint8_t> { ConfigWrapper<uint8_t> &getConfig() const override { return configs.dpadMappingProfile2; } };
struct ButtonProfile3Accessor : public NewSettingsAccessor<uint8_t> { ConfigWrapper<uint8_t> &getConfig() const override { return configs.dpadMappingProfile3; } };

// Can
struct CanResetOnErrorAccessor : public NewSettingsAccessor<bool> { ConfigWrapper<bool> &getConfig() const override { return configs.canResetOnError; } };
