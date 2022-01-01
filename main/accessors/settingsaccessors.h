#pragma once

// 3rdparty lib includes
#include <accessorinterface.h>

// local includes
#include "globals.h"
#include "utils.h"
#include "accessorhelpers.h"
#include "newsettings.h"

// Bms
#ifdef FEATURE_BMS
struct AutoConnectBmsAccessor : public RefAccessorSaveSettings<bool> { bool &getRef() const override { return settings.autoConnectBms; } };
#endif

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

// Bluetooth
#ifdef FEATURE_BLUETOOTH
struct AutoBluetoothModeAccessor : public RefAccessorSaveSettings<BluetoothMode> { BluetoothMode &getRef() const override { return settings.bluetoothSettings.autoBluetoothMode; } };
#endif

// Bluetooth Low Energy
#ifdef FEATURE_BLE
struct BleEnabledAccessor : public RefAccessorSaveSettings<bool> { bool &getRef() const override { return settings.bleSettings.bleEnabled; } };
#endif

// Cloud
#ifdef FEATURE_CLOUD
struct CloudEnabledAccessor : public RefAccessorSaveSettings<bool> { bool &getRef() const override { return settings.cloudSettings.cloudEnabled; } };
struct CloudTransmitTimeoutAccessor : public RefAccessorSaveSettings<int16_t> { int16_t &getRef() const override { return settings.cloudSettings.cloudTransmitTimeout; } };
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

struct WheelDiameterMmAccessor : public RefAccessorSaveSettings<int16_t> { int16_t &getRef() const override { return settings.controllerHardware.wheelDiameter; } };
struct WheelDiameterInchAccessor : public virtual espgui::AccessorInterface<float>
{
    float getValue() const override { return convertToInch(settings.controllerHardware.wheelDiameter); }
    espgui::AccessorInterface<int16_t>::setter_result_t setValue(float value) override
    {
        settings.controllerHardware.wheelDiameter = convertFromInch(value);
        if (!saveSettings())
            return tl::make_unexpected("saveSettings() failed!");
        return {};
    }
};
struct NumMagnetPolesAccessor : public RefAccessorSaveSettings<int16_t> { int16_t &getRef() const override { return settings.controllerHardware.numMagnetPoles; } };
struct SwapFrontBackAccessor : public RefAccessorSaveSettings<bool> {
    bool &getRef() const override { return settings.controllerHardware.swapFrontBack; }
#ifdef FEATURE_SERIAL
    void setValue(bool value) override { RefAccessorSaveSettings<bool>::setValue(value); updateSwapFrontBack(); };
#endif
};

// CAN
#ifdef FEATURE_CAN
struct SendFrontCanCmdAccessor : public RefAccessorSaveSettings<bool> { bool &getRef() const override { return settings.controllerHardware.sendFrontCanCmd; } };
struct SendBackCanCmdAccessor : public RefAccessorSaveSettings<bool> { bool &getRef() const override { return settings.controllerHardware.sendBackCanCmd; } };
struct CanTransmitTimeoutAccessor : public RefAccessorSaveSettings<int16_t> { int16_t &getRef() const override { return settings.controllerHardware.canTransmitTimeout; } };
struct CanReceiveTimeoutAccessor : public RefAccessorSaveSettings<int16_t> { int16_t &getRef() const override { return settings.controllerHardware.canReceiveTimeout; } };
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
struct GametrakXMinAccessor : public RefAccessorSaveSettings<int16_t> { int16_t &getRef() const override { return settings.boardcomputerHardware.gametrakXMin; } };
struct GametrakXMaxAccessor : public RefAccessorSaveSettings<int16_t> { int16_t &getRef() const override { return settings.boardcomputerHardware.gametrakXMax; } };
struct GametrakYMinAccessor : public RefAccessorSaveSettings<int16_t> { int16_t &getRef() const override { return settings.boardcomputerHardware.gametrakYMin; } };
struct GametrakYMaxAccessor : public RefAccessorSaveSettings<int16_t> { int16_t &getRef() const override { return settings.boardcomputerHardware.gametrakYMax; } };
struct GametrakDistMinAccessor : public RefAccessorSaveSettings<int16_t> { int16_t &getRef() const override { return settings.boardcomputerHardware.gametrakDistMin; } };
struct GametrakDistMaxAccessor : public RefAccessorSaveSettings<int16_t> { int16_t &getRef() const override { return settings.boardcomputerHardware.gametrakDistMax; } };
#endif
struct StatsUpdateRateAccessor : public RefAccessorSaveSettings<int16_t> { int16_t &getRef() const override { return settings.boardcomputerHardware.timersSettings.statsUpdateRate; } };

// Cloud
#ifdef FEATURE_CLOUD
struct CloudCollectRateAccessor : public RefAccessorSaveSettings<int16_t> { int16_t &getRef() const override { return settings.boardcomputerHardware.timersSettings.cloudCollectRate; } };
struct CloudSendRateAccessor : public RefAccessorSaveSettings<int16_t> { int16_t &getRef() const override { return settings.boardcomputerHardware.timersSettings.cloudSendRate; } };
#endif

#ifdef FEATURE_UDPCLOUD
struct UdpCloudSendIntervalAccessor : public RefAccessorSaveSettings<int16_t> { int16_t &getRef() const override { return settings.boardcomputerHardware.timersSettings.udpSendRateMs; } };
struct UdpCloudEnabledAccessor : public RefAccessorSaveSettings<bool> { bool &getRef() const override { return settings.udpCloudSettings.udpCloudEnabled; } };
struct CloudDebugEnableAccessor : public RefAccessorSaveSettings<bool> { bool &getRef() const override { return settings.udpCloudSettings.enableCloudDebug; } };
struct UdpUseStdStringAccessor : public RefAccessorSaveSettings<bool> { bool &getRef() const override { return settings.udpCloudSettings.udpUseStdString; } };
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
struct EnableLedAnimationAccessor : public RefAccessorSaveSettings<bool> { bool &getRef() const override { return settings.ledstrip.enableLedAnimation; } };
struct EnableBrakeLightsAccessor : public RefAccessorSaveSettings<bool> { bool &getRef() const override { return settings.ledstrip.enableBrakeLights; } };
struct LedsCountAccessor : public RefAccessorSaveSettings<int16_t> { int16_t &getRef() const override { return settings.ledstrip.ledsCount; } };
struct CenterOffsetAccessor : public RefAccessorSaveSettings<int16_t> { int16_t &getRef() const override { return settings.ledstrip.centerOffset; } };
struct SmallOffsetAccessor : public RefAccessorSaveSettings<int16_t> { int16_t &getRef() const override { return settings.ledstrip.smallOffset; } };
struct BigOffsetAccessor : public RefAccessorSaveSettings<int16_t> { int16_t &getRef() const override { return settings.ledstrip.bigOffset; } };
struct LedStripMaxMilliampsAccessor : public NewSettingsAccessor<uint32_t> { ConfigWrapper<uint32_t> &getConfig() const override { return configs.ledStripMaxMilliamps; } };
struct LedStripMaxAmpereAccessor : public virtual espgui::AccessorInterface<float>
{
    float getValue() const override
    {
        return configs.ledStripMaxMilliamps.value / 1000.f;
    }

    espgui::AccessorInterface<float>::setter_result_t setValue(float value) override
    {
        return configs.write_config(configs.ledStripMaxMilliamps, value * 1000);
    }
};
struct EnableBeepWhenBlinkAccessor : public RefAccessorSaveSettings<bool> { bool &getRef() const override { return settings.ledstrip.enableBeepWhenBlink; } };
struct EnableFullBlinkAccessor : public RefAccessorSaveSettings<bool> { bool &getRef() const override { return settings.ledstrip.enableFullBlink; } };
struct EnableLedstripStVOAccessor : public RefAccessorSaveSettings<bool> { bool &getRef() const override { return settings.ledstrip.enableStVO; } };
struct LedsStVOFrontOffsetAccessor : public RefAccessorSaveSettings<int16_t> { int16_t &getRef() const override { return settings.ledstrip.stvoFrontOffset; } };
struct LedsStVOFrontLengthAccessor : public RefAccessorSaveSettings<int16_t> { int16_t &getRef() const override { return settings.ledstrip.stvoFrontLength; } };
struct EnableLedstripStVOFrontlight : public RefAccessorSaveSettings<bool> { bool &getRef() const override { return settings.ledstrip.stvoFrontEnable; } };
struct AnimationMultiplierAccessor : public RefAccessorSaveSettings<int16_t> { int16_t &getRef() const override { return settings.ledstrip.animationMultiplier; } };
struct LedstripBrightnessAccessor : public RefAccessorSaveSettings<uint8_t> { uint8_t &getRef() const override { return settings.ledstrip.brightness; } };
struct LedstripEnableBlinkAnimationAccessor : public RefAccessorSaveSettings<bool> { bool &getRef() const override { return settings.ledstrip.enableAnimBlink; } };
#ifdef FEATURE_OTA
struct LedstripOtaAnimationAccessor : public RefAccessorSaveSettings<OtaAnimationModes> { OtaAnimationModes &getRef() const override { return settings.ledstrip.otaMode; } };
#endif
#endif

// Battery
struct BatterySeriesCellsAccessor : public RefAccessorSaveSettings<uint8_t> { uint8_t &getRef() const override { return settings.battery.cellsSeries; } };
struct BatteryParallelCellsAccessor : public RefAccessorSaveSettings<uint8_t> { uint8_t &getRef() const override { return settings.battery.cellsParallel; } };
struct BatteryWHperKMAccessor : public RefAccessorSaveSettings<uint16_t> { uint16_t &getRef() const override { return settings.battery.watthoursPerKilometer; } };
struct BatteryApplyCalibrationAccessor : public RefAccessorSaveSettings<bool> { bool &getRef() const override { return settings.battery.applyCalibration; } };

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
