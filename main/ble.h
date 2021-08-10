#pragma once

#define FEATURE_BLE
#define FEATURE_WIRELESS_CONFIG

// esp-idf includes
#include <esp_log.h>
// 3rdparty lib includes
#include <ArduinoJson.h>
#ifdef FEATURE_BLE
#include <NimBLEDevice.h>
#endif

// local includes
#include "globals.h"
#include "futurecpp.h"
#include "modes/remotecontrolmode.h"
#include "utils.h"

namespace {
#ifdef FEATURE_BLE
BLEServer *pServer{};
BLEService *pService{};
BLECharacteristic *livestatsCharacteristic{};
BLECharacteristic *remotecontrolCharacteristic{};
#ifdef FEATURE_WIRELESS_CONFIG
BLECharacteristic *wirelessConfig{};
#endif

void createBle();
void destroyBle();

class RemoteControlCallbacks : public NimBLECharacteristicCallbacks
{
public:
    void onWrite(NimBLECharacteristic* pCharacteristic) override;
};

#ifdef FEATURE_WIRELESS_CONFIG
class WirelessSettingsCallbacks : public NimBLECharacteristicCallbacks
{
public:
    void onWrite(NimBLECharacteristic* pCharacteristic) override;
};
#endif

RemoteControlCallbacks bleRemoteCallbacks;

#ifdef FEATURE_WIRELESS_CONFIG
WirelessSettingsCallbacks bleWirelessSettingsCallbacks;
#endif

void initBle()
{
    if (settings.bleSettings.bleEnabled)
        createBle();
}

void handleBle()
{
    if (settings.bleSettings.bleEnabled)
    {
        if (!pServer)
            createBle();

        if (livestatsCharacteristic->getSubscribedCount())
        {
            StaticJsonDocument<1024> doc;
            {
                auto arr = doc.createNestedArray("v");
                if (controllers.front.feedbackValid)
                    arr.add(fixBatVoltage(controllers.front.feedback.batVoltage));
                else
                    arr.add(nullptr);
                if (controllers.back.feedbackValid)
                    arr.add(fixBatVoltage(controllers.back.feedback.batVoltage));
                else
                    arr.add(nullptr);
            }

            {
                auto arr = doc.createNestedArray("t");
                if (controllers.front.feedbackValid)
                    arr.add(fixBoardTemp(controllers.front.feedback.boardTemp));
                else
                    arr.add(nullptr);
                if (controllers.back.feedbackValid)
                    arr.add(fixBoardTemp(controllers.back.feedback.boardTemp));
                else
                    arr.add(nullptr);
            }

            {
                auto arr = doc.createNestedArray("e");
                if (controllers.front.feedbackValid)
                {
                    arr.add(controllers.front.feedback.left.error);
                    arr.add(controllers.front.feedback.right.error);
                }
                else
                {
                    arr.add(nullptr);
                    arr.add(nullptr);
                }
                if (controllers.back.feedbackValid)
                {
                    arr.add(controllers.back.feedback.left.error);
                    arr.add(controllers.back.feedback.right.error);
                }
                else
                {
                    arr.add(nullptr);
                    arr.add(nullptr);
                }
            }

            {
                auto arr = doc.createNestedArray("s");
                if (controllers.front.feedbackValid)
                {
                    arr.add(convertToKmh(controllers.front.feedback.left.speed * (settings.controllerHardware.invertFrontLeft ? -1 : 1)));
                    arr.add(convertToKmh(controllers.front.feedback.right.speed * (settings.controllerHardware.invertFrontRight ? -1 : 1)));
                }
                else
                {
                    arr.add(nullptr);
                    arr.add(nullptr);
                }
                if (controllers.back.feedbackValid)
                {
                    arr.add(convertToKmh(controllers.back.feedback.left.speed * (settings.controllerHardware.invertBackLeft ? -1 : 1)));
                    arr.add(convertToKmh(controllers.back.feedback.right.speed * (settings.controllerHardware.invertBackRight ? -1 : 1)));
                }
                else
                {
                    arr.add(nullptr);
                    arr.add(nullptr);
                }
            }

            {
                auto arr = doc.createNestedArray("a");
                if (controllers.front.feedbackValid)
                {
                    arr.add(fixCurrent(controllers.front.feedback.left.dcLink) * 2);
                    arr.add(fixCurrent(controllers.front.feedback.right.dcLink) * 2);
                }
                else
                {
                    arr.add(nullptr);
                    arr.add(nullptr);
                }
                if (controllers.back.feedbackValid)
                {
                    arr.add(fixCurrent(controllers.back.feedback.left.dcLink) * 2);
                    arr.add(fixCurrent(controllers.back.feedback.right.dcLink) * 2);
                }
                else
                {
                    arr.add(nullptr);
                    arr.add(nullptr);
                }
            }

            std::string json;
            serializeJson(doc, json);

            livestatsCharacteristic->setValue(json);
            livestatsCharacteristic->notify();
        }

#ifdef FEATURE_WIRELESS_CONFIG

        if (wirelessConfig->getSubscribedCount())
        {
            StaticJsonDocument<1024> doc;
            {
                doc.add(42);
            }

            std::string json;
            serializeJson(doc, json);

            wirelessConfig->setValue(json);
            wirelessConfig->notify();
        }
#endif
    }
    else if (pServer)
    {
        destroyBle();
    }
}

void createBle()
{
    ESP_LOGI("BOBBY", "called");

    BLEDevice::init(deviceName);

    const auto serviceUuid{"0335e46c-f355-4ce6-8076-017de08cee98"};

    pServer = BLEDevice::createServer();

    pService = pServer->createService(serviceUuid);

    livestatsCharacteristic = pService->createCharacteristic("a48321ea-329f-4eab-a401-30e247211524", NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);
    remotecontrolCharacteristic = pService->createCharacteristic("4201def0-a264-43e6-946b-6b2d9612dfed", NIMBLE_PROPERTY::WRITE);
    remotecontrolCharacteristic->setCallbacks(&bleRemoteCallbacks);
#ifdef FEATURE_WIRELESS_CONFIG
    wirelessConfig = pService->createCharacteristic("4201def1-a264-43e6-946b-6b2d9612dfed", NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::WRITE);
    wirelessConfig->setCallbacks(&bleWirelessSettingsCallbacks);
#endif

    pService->start();

    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(serviceUuid);
    pAdvertising->setScanResponse(true);
    BLEDevice::startAdvertising();
}

void destroyBle()
{
    ESP_LOGI("BOBBY", "called");

    BLEDevice::deinit(true);

    pServer = {};
    pService = {};
    livestatsCharacteristic = {};
    remotecontrolCharacteristic = {};
    wirelessConfig = {};
}

void RemoteControlCallbacks::onWrite(NimBLECharacteristic* pCharacteristic)
{
    const auto &val = pCharacteristic->getValue();

    StaticJsonDocument<256> doc;
    if (const auto error = deserializeJson(doc, val))
    {
        ESP_LOGW(TAG, "ignoring cmd with invalid json: %.*s %s", val.size(), val.data(), error.c_str());
        return;
    }

    modes::remoteControlMode.setCommand(RemoteCommand{
        .frontLeft = doc["fl"].as<int16_t>(),
        .frontRight = doc["fr"].as<int16_t>(),
        .backLeft = doc["bl"].as<int16_t>(),
        .backRight = doc["br"].as<int16_t>()
    });
}

#ifdef FEATURE_WIRELESS_CONFIG
void WirelessSettingsCallbacks::onWrite(NimBLECharacteristic* pCharacteristic)
{
    const auto &val = pCharacteristic->getValue();

    StaticJsonDocument<256> doc;
    if (const auto error = deserializeJson(doc, val))
    {
        ESP_LOGW(TAG, "ignoring cmd with invalid json: %.*s %s", val.size(), val.data(), error.c_str());
        return;
    }

    const char* write_type = doc["type"].as<const char*>();

    if (strcmp(write_type, "wifi") == 0) {
        const int index = doc["wifi_index"].as<int>();
        ESP_LOGI(TAG, "[ble_config]: Set wifi%i: WiFi-SSID: %s, WiFi-Password: ***", doc["wifi_index"].as<int>(), doc["wifi_ssid"].as<const char*>());
        stringSettings.wifis[index].ssid = doc["wifi_ssid"].as<const char*>();
        stringSettings.wifis[index].key = doc["wifi_pass"].as<const char*>();
        saveSettings();
    } else {
        const auto deserialized = deserializeJson(doc, val);
        ESP_LOGW(TAG, "Unkown type %s -> json: %.*s %s", doc["type"].as<const char*>(), val.size(), val.data(), deserialized.c_str());
    }
}
#endif
#endif
}
