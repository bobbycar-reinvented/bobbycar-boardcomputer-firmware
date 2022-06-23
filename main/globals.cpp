#include "globals.h"

std::optional<int16_t> raw_gas, raw_brems;
std::optional<float> gas, brems;

#ifdef FEATURE_GAMETRAK
int16_t raw_gametrakX{};
int16_t raw_gametrakY{};
int16_t raw_gametrakDist{};
float gametrakX;
float gametrakY;
float gametrakDist;
#endif

float avgSpeed{};
float avgSpeedKmh{};
float sumCurrent{};
bool isLocked{};

std::optional<int> sunrise;
std::optional<int> sunset;
std::optional<espchrono::DateTime> sunrise_dt;

esp_chip_info_t chip_info;
esp_pm_config_esp32_t pm_config;

#ifdef GLOBALS_SOURCE
GLOBALS_SOURCE
#endif

bool simplified =
#if defined(HAS_SIMPLIFIED)
    true
#else
    false
#endif
;

ProfileSettings profileSettings;
SettingsPersister settingsPersister;

std::atomic<int8_t> rawButtonRequest;
std::atomic<int8_t> buttonRequest;

Controllers controllers;

#ifdef FEATURE_BLUETOOTH
BluetoothSerial bluetoothSerial;
#endif

ModeInterface *lastMode{};
ModeInterface *currentMode{};
