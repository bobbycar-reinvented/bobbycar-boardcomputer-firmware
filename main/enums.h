#pragma once

// local includes
#include <bobbytypesafeenum.h>

// ledstrip
#define OtaAnimationModesValues(x) \
    x(None) \
    x(GreenProgressBar) \
    x(ColorChangeAll)
DECLARE_BOBBYTYPESAFE_ENUM(OtaAnimationModes, : uint8_t, OtaAnimationModesValues)

#define LedstripAnimationValues(x) \
    x(DefaultRainbow) \
    x(Pride) \
    x(BetterRainbow) \
    x(SpeedSync) \
    x(CustomColor) \
    x(SnakeAnimation) \
    x(GasOMeter) \
    x(WarningAnimation) \
    x(Drehlicht) \
    x(MancheLKWsHabenDieseAnimation)
DECLARE_BOBBYTYPESAFE_ENUM(LedstripAnimation, : uint8_t, LedstripAnimationValues)

// battery
#define BatteryCellTypeValues(x) \
    x(_22P) \
    x(HG2) \
    x(MH1) \
    x(VTC5) \
    x(BAK_25R) \
    x(HE4)
DECLARE_BOBBYTYPESAFE_ENUM(BatteryCellType, : uint8_t, BatteryCellTypeValues)

// quick actions
#define BobbyQuickActionsValues(x) \
    x(NONE) \
    x(BLINK_LEFT) \
    x(BLINK_RIGHT) \
    x(HANDBREMSE) \
    x(OPEN_GARAGE) \
    x(WIFI_SCAN) \
    x(PWMOMAT) \
    x(HUPE) \
    x(COMPRESSOR_TOGGLE)

DECLARE_BOBBYTYPESAFE_ENUM(BobbyQuickActions, : uint8_t, BobbyQuickActionsValues)

// default status display
#define DefaultStatusDisplayValues(x) \
    x(Default) \
    x(Meters) \
    x(Battery) \
    x(BetterStatus)
DECLARE_BOBBYTYPESAFE_ENUM(DefaultStatusDisplay, : uint8_t, DefaultStatusDisplayValues)

// handbremse
#define HandbremseModeValues(x) \
    x(MOSFETS_OFF) \
    x(OPENMODE) \
    x(SPEED_0)
DECLARE_BOBBYTYPESAFE_ENUM(HandbremseMode, : uint8_t, HandbremseModeValues)

// setup
#define SetupStepValues(x) \
    x(INFORMATION) \
    x(BASIC_BUTTONS) \
    x(CALIBRATE_POTIS)
DECLARE_BOBBYTYPESAFE_ENUM(SetupStep, : uint8_t, SetupStepValues);
