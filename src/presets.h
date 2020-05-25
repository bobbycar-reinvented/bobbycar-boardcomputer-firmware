#pragma once

#include "settings.h"

namespace presets {
constexpr Settings::Limits defaultLimits {
    .iMotMax = DEFAULT_IMOTMAX,
    .iDcMax = DEFAULT_IDCMAX,
    .nMotMax = DEFAULT_NMOTMAX,
    .fieldWeakMax = DEFAULT_FIELDWEAKMAX,
    .phaseAdvMax = DEFAULT_FIELDADVMAX
};

constexpr Settings::Limits kidsLimits {
    .iMotMax = 5,
    .iDcMax = 7,
    .nMotMax = 500,
    .fieldWeakMax = 2,
    .phaseAdvMax = 20
};

constexpr Settings::ControllerHardware defaultControllerHardware {
    .enableFrontLeft = true,
    .enableFrontRight = true,
    .enableBackLeft = true,
    .enableBackRight = true,

    .invertFrontLeft = false,
    .invertFrontRight = true,
    .invertBackLeft = false,
    .invertBackRight = true,

    .wheelDiameter = 165,
    .numMagnetPoles = 15,
    .swapFrontBack = false
};

constexpr Settings::ControllerHardware mosfetsOffControllerHardware {
    .enableFrontLeft = false,
    .enableFrontRight = false,
    .enableBackLeft = false,
    .enableBackRight = false,

    .invertFrontLeft = false,
    .invertFrontRight = true,
    .invertBackLeft = false,
    .invertBackRight = true,

    .wheelDiameter = 165,
    .numMagnetPoles = 15,
    .swapFrontBack = false
};

constexpr Settings::ControllerHardware spinnerControllerHardware {
    .enableFrontLeft = true,
    .enableFrontRight = true,
    .enableBackLeft = true,
    .enableBackRight = true,

    .invertFrontLeft = false,
    .invertFrontRight = false,
    .invertBackLeft = false,
    .invertBackRight = false,

    .wheelDiameter = 165,
    .numMagnetPoles = 15,
    .swapFrontBack = false
};

constexpr Settings::BoardcomputerHardware defaultBoardcomputerHardware {
    .sampleCount = 100,
    .gasMin = DEFAULT_GASMIN,
    .gasMax = DEFAULT_GASMAX,
    .bremsMin = DEFAULT_BREMSMIN,
    .bremsMax = DEFAULT_BREMSMAX,
    .swapScreenBytes = DEFAULT_SWAPSCREENBYTES
};

constexpr Settings::DefaultMode defaultDefaultMode {
    .ctrlTyp = ControlType::FieldOrientedControl,
    .ctrlMod = ControlMode::Torque,
    .enableSmoothing = true,
    .smoothing = 20,
    .frontPercentage = 100,
    .backPercentage = 100,
    .add_schwelle = 950,
    .gas1_wert = 1250,
    .gas2_wert = 1250,
    .brems1_wert = 250,
    .brems2_wert = 750
};

constexpr Settings::TempomatMode defaultTempomatMode {
    .ctrlTyp = ControlType::FieldOrientedControl,
    .ctrlMod = ControlMode::Speed
};

constexpr Settings::LarsmMode defaultLarsmMode {
    .mode = LarsmModeMode::Mode4,
    .iterations = 5
};

constexpr Settings defaultSettings{
#ifdef FEATURE_BMS
    .autoConnectBms = false,
#endif
    .reverseBeep = true,
    .reverseBeepFreq0 = 3,
    .reverseBeepFreq1 = 0,
    .reverseBeepDuration0 = 500,
    .reverseBeepDuration1 = 500,
    .limits = defaultLimits,
    .controllerHardware = defaultControllerHardware,
    .boardcomputerHardware = defaultBoardcomputerHardware,
    .defaultMode = defaultDefaultMode,
    .tempomatMode = defaultTempomatMode,
    .larsmMode = defaultLarsmMode
};
}
