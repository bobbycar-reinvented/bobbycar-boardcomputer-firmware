#include <cstdio>

#include <esp_wifi_types.h>
#ifdef FEATURE_CLOUD
#include <esp_websocket_client.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#endif

#include <Arduino.h>
#include <HardwareSerial.h>
#include <WiFi.h>
#include <WiFiMulti.h>

#include "bobbycar-protocol/bobbycar-common.h"
#include "bobbycar-protocol/bobbycar-serial.h"

#include "globals.h"
#include "modes/defaultmode.h"
#include "modes/tempomatmode.h"
#include "displays/menus/aboutmenu.h"
#include "displays/menus/accesspointwifisettingsmenu.h"
#ifdef FEATURE_BLUETOOTH
#include "displays/menus/bluetoothsettingsmenu.h"
#endif
#include "displays/menus/bmsmenu.h"
#include "displays/menus/buzzermenu.h"
#include "displays/menus/commanddebugmenu.h"
#include "displays/menus/debugmenu.h"
#include "displays/menus/defaultmodesettingsmenu.h"
#include "displays/menus/demosmenu.h"
#include "displays/menus/dynamicdebugmenu.h"
#include "displays/menus/enablemenu.h"
#include "displays/menus/feedbackdebugmenu.h"
#include "displays/menus/gametrakmodesettingsmenu.h"
#include "displays/menus/genericwifisettingsmenu.h"
#include "displays/menus/graphsmenu.h"
#include "displays/menus/controllerhardwaresettingsmenu.h"
#include "displays/menus/invertmenu.h"
#include "displays/menus/larsmmodesettingsmenu.h"
#include "displays/menus/limitssettingsmenu.h"
#include "displays/menus/mainmenu.h"
#include "displays/menus/tempomatmodesettingsmenu.h"
#include "displays/menus/modessettingsmenu.h"
#include "displays/menus/mosfetsmenu.h"
#include "displays/menus/motorfeedbackdebugmenu.h"
#include "displays/menus/motorstatedebugmenu.h"
#include "displays/menus/profilesmenu.h"
#include "displays/menus/presetsmenu.h"
#include "displays/menus/boardcomputerhardwaresettingsmenu.h"
#include "displays/menus/selectmodemenu.h"
#include "displays/menus/settingsmenu.h"
#include "displays/menus/stationwifisettingsmenu.h"
#include "displays/menus/timersmenu.h"
#include "displays/menus/wifiscanmenu.h"
#include "displays/menus/wifisettingsmenu.h"
#include "displays/bmsdisplay.h"
#include "displays/calibratedisplay.h"
#include "displays/dpad5wiredebugdisplay.h"
#include "displays/gameoflifedisplay.h"
#include "displays/gametrakcalibratedisplay.h"
#include "displays/lockscreen.h"
#include "displays/metersdisplay.h"
#include "displays/pingpongdisplay.h"
#include "displays/poweroffdisplay.h"
#include "displays/powersupplydisplay.h"
#include "displays/spirodisplay.h"
#include "displays/starfielddisplay.h"
#include "displays/statusdisplay.h"
#include "displays/updatedisplay.h"
#include "screens.h"
#include "dpad.h"
#include "dpad3wire.h"
#include "dpad5wire.h"
#include "rotary.h"
#include "serialhandler.h"
#include "ota.h"
#include "presets.h"
#include "statistics.h"
#include "actions/wifisoftapaction.h"
#ifdef FEATURE_BLUETOOTH
#include "actions/bluetoothbeginaction.h"
#include "actions/bluetoothbeginmasteraction.h"
#include "actions/bluetoothconnectbmsaction.h"
#endif
#include "bobby_webserver.h"
#include "types.h"
#ifdef FEATURE_CAN
#include "can.h"
#endif

namespace {
ModeInterface *lastMode{};
millis_t lastPotiRead{};
millis_t lastModeUpdate{};
millis_t lastStatsUpdate{};
millis_t lastDisplayUpdate{};
millis_t lastDisplayRedraw{};
}

void printMemoryStats(const char *s)
{
    Serial.printf("MEMORY %s 8bit: %u 32bit: %u\r\n",
                  s,
                  heap_caps_get_free_size(MALLOC_CAP_INTERNAL|MALLOC_CAP_8BIT),
                  heap_caps_get_free_size(MALLOC_CAP_INTERNAL|MALLOC_CAP_32BIT));
}

#ifdef FEATURE_CLOUD
void cloudTask(void*)
{
    const esp_websocket_client_config_t config = {
        .uri = "ws://iot.wattpilot.io:8080/charger/bobbycar1",
    };
    esp_websocket_client_handle_t handle = esp_websocket_client_init(&config);

    if (handle)
    {
        Serial.println("esp websocket init succeeded");

        if (const auto result = esp_websocket_client_start(handle); result == ESP_OK)
        {
            Serial.println("esp websocket start succeeded");

            while (true)
            {
                if (esp_websocket_client_is_connected(handle))
                {
                    std::string msg = "{"
                        "\"type\": \"fullStatus\","
                        "\"partial\": false, "
                        "\"status\": {"
                            "\"millis\":" + std::to_string(millis()) + ","
                            "\"front.valid\":" + (controllers.front.feedbackValid?"true":"false") + ","
                            "\"back.valid\":" + (controllers.back.feedbackValid?"true":"false") + ","
                            "\"front.left.pwm\":" + std::to_string(controllers.front.command.left.pwm) + ","
                            "\"front.right.pwm\":" + std::to_string(controllers.front.command.right.pwm) + ","
                            "\"back.left.pwm\":" + std::to_string(controllers.back.command.left.pwm) + ","
                            "\"back.right.pwm\":" + std::to_string(controllers.back.command.right.pwm) + ","
                            "\"front.volt\":" + std::to_string(controllers.front.feedback.batVoltage) + ","
                            "\"back.volt\":" + std::to_string(controllers.back.feedback.batVoltage) + ","
                            "\"front.temp\":" + std::to_string(controllers.front.feedback.boardTemp) + ","
                            "\"back.temp\":" + std::to_string(controllers.back.feedback.boardTemp) + ","
                            "\"front.bad\":" + std::to_string(controllers.front.feedback.timeoutCntSerial) + ","
                            "\"back.bad\":" + std::to_string(controllers.back.feedback.timeoutCntSerial) + ","
                            "\"front.left.speed\":" + std::to_string(controllers.front.feedback.left.speed) + ","
                            "\"front.right.speed\":" + std::to_string(controllers.front.feedback.right.speed) + ","
                            "\"back.left.speed\":" + std::to_string(controllers.back.feedback.left.speed) + ","
                            "\"back.right.speed\":" + std::to_string(controllers.back.feedback.right.speed) + ","
                            "\"front.left.current\":" + std::to_string(controllers.front.feedback.left.current) + ","
                            "\"front.right.current\":" + std::to_string(controllers.front.feedback.right.current) + ","
                            "\"back.left.current\":" + std::to_string(controllers.back.feedback.left.current) + ","
                            "\"back.right.current\":" + std::to_string(controllers.back.feedback.right.current) + ","
                            "\"front.left.error\":" + std::to_string(controllers.front.feedback.left.error) + ","
                            "\"front.right.error\":" + std::to_string(controllers.front.feedback.right.error) + ","
                            "\"back.left.error\":" + std::to_string(controllers.back.feedback.left.error) + ","
                            "\"back.right.error\":" + std::to_string(controllers.back.feedback.right.error) +
                        "}"
                    "}";

                    const auto sent = esp_websocket_client_send_text(handle, msg.c_str(), msg.length(), 1000 / portTICK_PERIOD_MS);
                    if (sent == msg.length())
                        Serial.println("Sent cloud message");
                    else
                        Serial.printf("sent=%i, msgsize=%i\r\n", sent, msg.length());
                }
                else
                    Serial.println("Not sending cloud because not connected");

                delay(100);
            }
        }
        else
            Serial.printf("esp websocket start failed with %s\r\n", esp_err_to_name(result));
    }
    else
        Serial.println("esp websocket init failed");

    vTaskDelete(NULL);
}
#endif

void setup()
{
    Serial.begin(115200);
    Serial.setDebugOutput(true);
    //Serial.println("setup()");

#ifdef PINS_LED
    pinMode(PINS_LED, OUTPUT);
    digitalWrite(PINS_LED, LOW);
#endif

    printMemoryStats("setup()");

    pinMode(3, INPUT_PULLUP);

    currentlyReverseBeeping = false;

    initScreen();
    printMemoryStats("initScreen()");

#ifdef FEATURE_DPAD
    bootLabel.redraw("dpad");
    dpad::init();
#endif

#ifdef FEATURE_DPAD_3WIRESW
    bootLabel.redraw("dpad3wire");
    dpad3wire::init();
#endif

#ifdef FEATURE_DPAD_5WIRESW
    bootLabel.redraw("dpad5wire");
    dpad5wire::init();
#endif

#ifdef FEATURE_ROTARY
    bootLabel.redraw("rotary");
    initRotary();
#endif

#ifdef FEATURE_MOSFETS
    bootLabel.redraw("mosfets");
    pinMode(PINS_MOSFET0, OUTPUT);
    pinMode(PINS_MOSFET1, OUTPUT);
    pinMode(PINS_MOSFET2, OUTPUT);

    digitalWrite(PINS_MOSFET0, LOW);
    digitalWrite(PINS_MOSFET1, LOW);
    digitalWrite(PINS_MOSFET2, LOW);
#endif

    bootLabel.redraw("settings");
    settings = presets::defaultSettings;

    if (settingsPersister.init())
    {
        if (settingsPersister.openProfile(0))
        {
            loadSettings();
        }
    }
    printMemoryStats("loadSettings()");

#ifdef FEATURE_SERIAL
    bootLabel.redraw("swap front back");
    updateSwapFrontBack();
    printMemoryStats("swapFronBack()");
#endif

    bootLabel.redraw("deviceName");
    {
        uint8_t macAddress[6];
        WiFi.macAddress(&macAddress[0]);
        std::sprintf(deviceName, STRING(DEVICE_PREFIX) "_%02hhx%02hhx%02hhx", macAddress[3], macAddress[4], macAddress[5]);
    }
    printMemoryStats("deviceName");

    bootLabel.redraw("setHostname");
    if (!WiFi.setHostname(deviceName))
        Serial.println("Could not setHostname");
    printMemoryStats("setHostname()");

    bootLabel.redraw("softAPsetHostname");
    if (!WiFi.softAPsetHostname(deviceName))
        Serial.println("Could not softAPsetHostname");
    printMemoryStats("softAPsetHostname()");

    bootLabel.redraw("WiFi mode");
    if (!WiFi.mode(settings.wifiSettings.autoWifiMode))
        Serial.println("Could not set mode to WIFI_AP_STA");
    printMemoryStats("WiFi.mode()");

    if (settings.wifiSettings.autoEnableAp)
    {
        bootLabel.redraw("WiFi softAp");
        WifiSoftApAction{}.triggered();
    }
    printMemoryStats("WifiSoftApAction()");

    bootLabel.redraw("WiFi begin");
    if (!WiFi.begin("realraum", "r3alraum"))
        Serial.println("Could not begin WiFi");
    printMemoryStats("WiFi.begin()");

#ifdef FEATURE_BLUETOOTH
    if (settings.bluetoothSettings.autoBluetoothMode == BluetoothMode::Master)
    {
        bootLabel.redraw("bluetooth begin master");
        BluetoothBeginMasterAction{}.triggered();
        printMemoryStats("BluetoothBeginMasterAction()");
#ifdef FEATURE_BMS
        if (settings.autoConnectBms)
        {
            bootLabel.redraw("connect BMS");
            BluetoothConnectBmsAction{}.triggered();
            printMemoryStats("BluetoothConnectBmsAction()");
        }
#endif
    }
    else if (settings.bluetoothSettings.autoBluetoothMode == BluetoothMode::Slave)
    {
        bootLabel.redraw("bluetooth begin");
        BluetoothBeginAction{}.triggered();
        printMemoryStats("BluetoothBeginAction()");
    }
#endif

#ifdef FEATURE_CAN
    initCan();
#endif

#ifdef FEATURE_SERIAL
    bootLabel.redraw("front Serial begin");
    controllers.front.serial.get().begin(38400, SERIAL_8N1, PINS_RX1, PINS_TX1);

    bootLabel.redraw("back Serial begin");
    controllers.back.serial.get().begin(38400, SERIAL_8N1, PINS_RX2, PINS_TX2);
#endif

    raw_gas = 0;
    raw_brems = 0;
    gas = 0;
    brems = 0;

    for (Controller &controller : controllers)
        controller.command.buzzer = {};

    currentMode = &modes::defaultMode;

#ifdef FEATURE_ARDUINOOTA
    bootLabel.redraw("ota");
    initOta();
    printMemoryStats("initOta()");
#endif

#ifdef FEATURE_WEBSERVER
    bootLabel.redraw("webserver");
    initWebserver();
    printMemoryStats("initWebserver()");
#endif

    bootLabel.redraw("potis");
    readPotis();
    printMemoryStats("readPotis()");

#ifdef FEATURE_CLOUD
    if (const auto result = xTaskCreatePinnedToCore(cloudTask, "cloudTask", 4096, nullptr, 10, nullptr, 1); result == pdTRUE)
        Serial.println("cloud task create succeeded");
    else
        Serial.printf("cloud task create failed\r\n");
#endif

#if defined(FEATURE_DPAD_5WIRESW) && defined(DPAD_5WIRESW_DEBUG)
    switchScreen<DPad5WireDebugDisplay>();
    return;
#endif

    if (gas > 200.f || brems > 200.f)
        switchScreen<CalibrateDisplay>(true);
    else
        switchScreen<StatusDisplay>();

    printMemoryStats("switchScreen()");
}

void loop()
{
    //Serial.println("loop()");
    //printMemoryStats("loop()");

    const auto now = millis();

#ifdef FEATURE_DPAD
    dpad::update();
#endif

#ifdef FEATURE_DPAD_3WIRESW
    dpad3wire::update();
#endif

#ifdef FEATURE_DPAD_5WIRESW
    dpad5wire::update();
#endif

    if (!lastPotiRead || now - lastPotiRead >= 1000/settings.boardcomputerHardware.timersSettings.potiReadRate)
    {
        readPotis();

        lastPotiRead = now;
    }

    if (!lastModeUpdate || now - lastModeUpdate >= 1000/settings.boardcomputerHardware.timersSettings.modeUpdateRate)
    {
        if (lastMode != currentMode)
        {
            if (lastMode)
                lastMode->stop();
            lastMode = currentMode;
            if (currentMode)
                currentMode->start();
        }

        if (currentMode)
            currentMode->update();

        lastModeUpdate = now;

        performance.current++;
    }

    if (!lastStatsUpdate || now - lastStatsUpdate >= 1000/settings.boardcomputerHardware.timersSettings.statsUpdateRate)
    {
        updateAccumulators();
        pushStats();
        lastStatsUpdate = now;
    }

    if (!lastDisplayUpdate || now - lastDisplayUpdate >= 1000/settings.boardcomputerHardware.timersSettings.displayUpdateRate)
    {
        updateDisplay();

        lastDisplayUpdate = now;
    }

    if (!lastDisplayRedraw || now - lastDisplayRedraw >= 1000/settings.boardcomputerHardware.timersSettings.displayRedrawRate)
    {
        redrawDisplay();

        lastDisplayRedraw = now;
    }

    if (now - performance.lastTime >= 1000)
    {
        performance.last = performance.current;
        performance.current = 0;
        performance.lastTime = now;
    }

#ifdef FEATURE_CAN
    for (int i = 0; i < 4; i++)
        if (!parseCanInput())
            break;
#endif

#ifdef FEATURE_SERIAL
    for (Controller &controller : controllers)
        controller.parser.update();
#endif

    handleSerial();

#ifdef FEATURE_ARDUINOOTA
    handleOta();
#endif

#ifdef FEATURE_WEBSERVER
    handleWebserver();
#endif

#ifdef FEATURE_BMS
    bms::update();
#endif
}
