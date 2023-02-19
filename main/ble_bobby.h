#pragma once

// esp-idf includes
#include <NimBLEDevice.h>

namespace bobby::ble {

extern BLEServer *pServer;
extern BLEService *pService;
extern BLECharacteristic *livestatsCharacteristic;
extern BLECharacteristic *remotecontrolCharacteristic;
extern BLECharacteristic *wirelessConfig;
extern BLECharacteristic *getwifilist;

void initBle();

void handleBle();

struct RemoteCommand
{
    int16_t frontLeft{};
    int16_t frontRight{};
    int16_t backLeft{};
    int16_t backRight{};
};

} // namespace bobby::ble
