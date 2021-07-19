#pragma once

// 3rdparty lib includes
#ifdef FEATURE_BLE
#include <NimBLEDevice.h>
#endif

// local includes
#include "globals.h"
#include "futurecpp.h"

namespace {
#ifdef FEATURE_BLE
BLEServer *pServer{};
BLEService *pService{};
int bleIndex{};

struct {
    struct {
        BLECharacteristic *voltage{};
        BLECharacteristic *temperature{};

        struct {
            BLECharacteristic *error{};
            BLECharacteristic *speed{};
            BLECharacteristic *dcLink{};
        } left, right;
    } front, back;
} characteristics;

void initBle()
{
    BLEDevice::init(deviceName);

    const auto serviceUuid{"0335e46c-f355-4ce6-8076-017de08cee98"};

    pServer = BLEDevice::createServer();

    pService = pServer->createService(serviceUuid);

    characteristics.front.voltage = pService->createCharacteristic("a48321ea-329f-4eab-a401-30e247211524", NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);
    characteristics.back.voltage = pService->createCharacteristic("4201def0-a264-43e6-946b-6b2d9612dfed", NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);

    characteristics.front.temperature = pService->createCharacteristic("4799e23f-6448-4786-900b-b5c3f3c17a9c", NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);
    characteristics.back.temperature = pService->createCharacteristic("3c32b7bb-8d9b-4055-8ea0-5b6764111024", NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);

    characteristics.front.left.error = pService->createCharacteristic("f84b3a9b-1b2c-4075-acbe-016a2166976c", NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);
    characteristics.front.right.error = pService->createCharacteristic("eed4b709-5a65-4a5b-8e07-512f9661533d", NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);
    characteristics.back.left.error = pService->createCharacteristic("89d143f5-9ae2-4f7e-9235-643a3a7e21df", NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);
    characteristics.back.right.error = pService->createCharacteristic("0fb377f1-7527-4966-aaf0-8bd56f2ddd3f", NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);

    characteristics.front.left.speed = pService->createCharacteristic("c6f959e8-0ec3-4bdd-88ad-6ad993fc81e9", NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);
    characteristics.front.right.speed = pService->createCharacteristic("ce53f135-8f20-4b80-abb9-31da81d62716", NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);
    characteristics.back.left.speed = pService->createCharacteristic("9a1dd1fe-3f14-4af1-bc5e-3f70edcae54b", NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);
    characteristics.back.right.speed = pService->createCharacteristic("7de1a823-682e-438f-9201-3a80c3911f1a", NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);

    characteristics.front.left.dcLink = pService->createCharacteristic("f404416f-2a77-41c6-a35f-7d10ec38376d", NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);
    characteristics.front.right.dcLink = pService->createCharacteristic("452dd012-3f12-428c-8746-40c6b6c73c40", NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);
    characteristics.back.left.dcLink = pService->createCharacteristic("9dc455a3-718e-4d62-b0e7-1c0cb2a8bbd3", NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);
    characteristics.back.right.dcLink = pService->createCharacteristic("90a66506-1d78-4ba2-b074-e1153fbf5216", NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);

    pService->start();

    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(serviceUuid);
    pAdvertising->setScanResponse(true);
    BLEDevice::startAdvertising();
}

void handleBle()
{
    switch (bleIndex++) {
    default:
        bleIndex = 1;
    [[fallthrough]];
    case 0:
        characteristics.front.voltage->setValue(controllers.front.feedbackValid ? fmt::format("{:.2f}", fixBatVoltage(controllers.front.feedback.batVoltage)) : "");
        characteristics.front.voltage->notify();
        break;
    case 1:
        characteristics.back.voltage->setValue(controllers.back.feedbackValid ? fmt::format("{:.2f}", fixBatVoltage(controllers.back.feedback.batVoltage)) : "");
        characteristics.back.voltage->notify();
        break;
    case 2:
        characteristics.front.temperature->setValue(controllers.front.feedbackValid ? fmt::format("{:.2f}", fixBoardTemp(controllers.front.feedback.boardTemp)) : "");
        characteristics.front.temperature->notify();
        break;
    case 3:
        characteristics.back.temperature->setValue(controllers.back.feedbackValid ? fmt::format("{:.2f}", fixBoardTemp(controllers.back.feedback.boardTemp)) : "");
        characteristics.back.temperature->notify();
        break;

    case 4:
        characteristics.front.left.error->setValue(controllers.front.feedbackValid ? fmt::format("{}", controllers.front.feedback.left.error) : "");
        characteristics.front.left.error->notify();
        break;
    case 5:
        characteristics.front.right.error->setValue(controllers.front.feedbackValid ? fmt::format("{}", controllers.front.feedback.right.error) : "");
        characteristics.front.right.error->notify();
        break;
    case 6:
        characteristics.back.left.error->setValue(controllers.back.feedbackValid ? fmt::format("{}", controllers.back.feedback.left.error) : "");
        characteristics.back.left.error->notify();
        break;
    case 7:
        characteristics.back.right.error->setValue(controllers.back.feedbackValid ? fmt::format("{}", controllers.back.feedback.right.error) : "");
        characteristics.back.right.error->notify();
        break;

    case 8:
        characteristics.front.left.speed->setValue(controllers.front.feedbackValid ? fmt::format("{:.2f}", convertToKmh(controllers.front.feedback.left.speed * (settings.controllerHardware.invertFrontLeft ? -1 : 1))) : "");
        characteristics.front.left.speed->notify();
        break;
    case 9:
        characteristics.front.right.speed->setValue(controllers.front.feedbackValid ? fmt::format("{:.2f}", convertToKmh(controllers.front.feedback.right.speed * (settings.controllerHardware.invertFrontRight ? -1 : 1))) : "");
        characteristics.front.right.speed->notify();
        break;
    case 10:
        characteristics.back.left.speed->setValue(controllers.back.feedbackValid ? fmt::format("{:.2f}", convertToKmh(controllers.back.feedback.left.speed * (settings.controllerHardware.invertBackLeft ? -1 : 1))) : "");
        characteristics.back.left.speed->notify();
        break;
    case 11:
        characteristics.back.right.speed->setValue(controllers.back.feedbackValid ? fmt::format("{:.2f}", convertToKmh(controllers.back.feedback.right.speed * (settings.controllerHardware.invertBackRight ? -1 : 1))) : "");
        characteristics.back.right.speed->notify();
        break;

    case 12:
        characteristics.front.left.dcLink->setValue(controllers.front.feedbackValid ? fmt::format("{:.2f}", fixCurrent(controllers.front.feedback.left.dcLink)) : "");
        characteristics.front.left.dcLink->notify();
        break;
    case 13:
        characteristics.front.right.dcLink->setValue(controllers.front.feedbackValid ? fmt::format("{:.2f}", fixCurrent(controllers.front.feedback.right.dcLink)) : "");
        characteristics.front.right.dcLink->notify();
        break;
    case 14:
        characteristics.back.left.dcLink->setValue(controllers.back.feedbackValid ? fmt::format("{:.2f}", fixCurrent(controllers.back.feedback.left.dcLink)) : "");
        characteristics.back.left.dcLink->notify();
        break;
    case 15:
        characteristics.back.right.dcLink->setValue(controllers.back.feedbackValid ? fmt::format("{:.2f}", fixCurrent(controllers.back.feedback.right.dcLink)) : "");
        characteristics.back.right.dcLink->notify();
        break;
    }
}
#endif
}
