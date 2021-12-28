#pragma once

#ifdef FEATURE_BLE

// esp-idf includes
#include <NimBLEDevice.h>

extern BLEServer *pServer;
extern BLEService *pService;
extern BLECharacteristic *livestatsCharacteristic;
extern BLECharacteristic *remotecontrolCharacteristic;
#ifdef FEATURE_WIRELESS_CONFIG
extern BLECharacteristic *wirelessConfig;
extern BLECharacteristic *getwifilist;
#endif // FEATURE_WIRELESS_CONFIG

void initBle();

void handleBle();

#endif
