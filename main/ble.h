#pragma once

// 3rdparty lib includes
#ifdef FEATURE_BLE
#include <NimBLEDevice.h>
#endif

// local includes
#include "globals.h"

namespace {
#ifdef FEATURE_BLE
BLEServer *pServer{};
BLEService *pService{};

struct {
    struct {
        struct {
            BLECharacteristic *speed{};
        } left, right;
    } front, back;
} characteristics;

void initBle()
{
    BLEDevice::init(deviceName);

    const auto serviceUuid{"0335e46c-f355-4ce6-8076-017de08cee98"};

    pServer = BLEDevice::createServer();

    pService = pServer->createService(serviceUuid);

    characteristics.front.left.speed = pService->createCharacteristic("81287506-8985-4cea-9a58-92fc5ad2c570", NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);
    characteristics.front.right.speed = pService->createCharacteristic("2f326a23-a676-4f87-b5cb-37a8fd7fe466", NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);
    characteristics.back.left.speed = pService->createCharacteristic("a7f951c0-e984-460d-98ed-0d54c64092d5", NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);
    characteristics.back.right.speed = pService->createCharacteristic("14efe73f-6e34-49b3-b2c7-b513f3f5aee2", NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);

    pService->start();

    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(serviceUuid);
    pAdvertising->setScanResponse(true);
    BLEDevice::startAdvertising();
}

void handleBle()
{
    characteristics.front.left.speed->setValue(controllers.front.feedbackValid ? fmt::format("{:.2f}", convertToKmh(controllers.front.feedback.left.speed)) : "");
    characteristics.front.left.speed->notify();
    characteristics.front.right.speed->setValue(controllers.front.feedbackValid ? fmt::format("{:.2f}", convertToKmh(controllers.front.feedback.right.speed)) : "");
    characteristics.front.right.speed->notify();
    characteristics.back.left.speed->setValue(controllers.back.feedbackValid ? fmt::format("{:.2f}", convertToKmh(controllers.back.feedback.left.speed)) : "");
    characteristics.back.left.speed->notify();
    characteristics.back.right.speed->setValue(controllers.back.feedbackValid ? fmt::format("{:.2f}", convertToKmh(controllers.back.feedback.right.speed)) : "");
    characteristics.back.right.speed->notify();
}
#endif
}
