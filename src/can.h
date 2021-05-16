#pragma once

#include <esp_log.h>
#include <driver/gpio.h>
#include <driver/can.h>

#include <Arduino.h>

#include "types.h"
#include "globals.h"

namespace {
millis_t m_lastCanFeedback{};

void initCan()
{
    ESP_LOGI("CAN", "hello world");

    can_general_config_t g_config = CAN_GENERAL_CONFIG_DEFAULT(GPIO_NUM_21, GPIO_NUM_22, CAN_MODE_NORMAL);
    can_timing_config_t t_config CAN_TIMING_CONFIG_250KBITS();
    can_filter_config_t f_config = CAN_FILTER_CONFIG_ACCEPT_ALL();

    if (const auto result = can_driver_install(&g_config, &t_config, &f_config); result == ESP_OK)
    {
        ESP_LOGI("CAN", "can_driver_install() succeeded");
    }
    else
    {
        ESP_LOGE("CAN", "can_driver_install() failed with %s", esp_err_to_name(result));
        return;
    }

    if (const auto result = can_start(); result == ESP_OK)
    {
        ESP_LOGI("CAN", "can_start() succeeded");
    }
    else
    {
        ESP_LOGE("CAN", "can_start() failed with %s", esp_err_to_name(result));

        if (const auto result = can_driver_uninstall(); result == ESP_OK)
        {
            ESP_LOGI("CAN", "can_driver_uninstall() succeeded");
        }
        else
        {
            ESP_LOGE("CAN", "can_driver_uninstall() failed with %s", esp_err_to_name(result));
        }

        return;
    }
}

void parseCanInput()
{
    can_message_t message;
    if (const auto result = can_receive(&message, pdMS_TO_TICKS(200)); result != ESP_OK)
    {
        controllers.front.feedbackValid = millis() - m_lastCanFeedback <= 100;

        if (result != ESP_ERR_TIMEOUT)
            ESP_LOGE("CAN", "can_receive() failed with %s", esp_err_to_name(result));
        return;
    }

    enum { //                         vv
        DeviceTypeMotorController = 0b00000000000
    };

        enum { //                         ..vv
            MotorControllerRec =        0b00000000000,
            MotorControllerSend =       0b00010000000,
            };

    enum { //                         ....vvvvv
        MotorControllerDcLink =     0b00000000000,
        MotorControllerSpeed =      0b00000000100,
        MotorControllerError =      0b00000001000,
        MotorControllerAngle =      0b00000001100,
        MotorControllerDcPhaA =     0b00000010000,
        MotorControllerDcPhaB =     0b00000010100,
        MotorControllerDcPhaC =     0b00000011000,
        MotorControllerChops =      0b00000011100,
        MotorControllerHall =       0b00000100000,
        MotorControllerVoltage =    0b00000100100,
        MotorControllerTemp =       0b00000101000
    };

        enum { //                         .........v
            MotorControllerFront =      0b00000000000,
            MotorControllerBack =       0b00000000010,
            };

        enum { //                         ..........v
            MotorControllerLeft =       0b00000000000,
            MotorControllerRight =      0b00000000001,
            };

        enum {
            MotorControllerFrontLeftDcLink = DeviceTypeMotorController | MotorControllerSend | MotorControllerDcLink | MotorControllerFront | MotorControllerLeft,
            MotorControllerFrontRightDcLink = DeviceTypeMotorController | MotorControllerSend | MotorControllerDcLink | MotorControllerFront | MotorControllerRight,
            MotorControllerBackLeftDcLink = DeviceTypeMotorController | MotorControllerSend | MotorControllerDcLink | MotorControllerBack | MotorControllerLeft,
            MotorControllerBackRightDcLink = DeviceTypeMotorController | MotorControllerSend | MotorControllerDcLink | MotorControllerBack | MotorControllerRight,

            MotorControllerFrontLeftSpeed = DeviceTypeMotorController | MotorControllerSend | MotorControllerSpeed | MotorControllerFront | MotorControllerLeft,
            MotorControllerFrontRightSpeed = DeviceTypeMotorController | MotorControllerSend | MotorControllerSpeed | MotorControllerFront | MotorControllerRight,
            MotorControllerBackLeftSpeed = DeviceTypeMotorController | MotorControllerSend | MotorControllerSpeed | MotorControllerBack | MotorControllerLeft,
            MotorControllerBackRightSpeed = DeviceTypeMotorController | MotorControllerSend | MotorControllerSpeed | MotorControllerBack | MotorControllerRight,

            MotorControllerFrontLeftError = DeviceTypeMotorController | MotorControllerSend | MotorControllerError | MotorControllerFront | MotorControllerLeft,
            MotorControllerFrontRightError = DeviceTypeMotorController | MotorControllerSend | MotorControllerError | MotorControllerFront | MotorControllerRight,
            MotorControllerBackLeftError = DeviceTypeMotorController | MotorControllerSend | MotorControllerError | MotorControllerBack | MotorControllerLeft,
            MotorControllerBackRightError = DeviceTypeMotorController | MotorControllerSend | MotorControllerError | MotorControllerBack | MotorControllerRight,

            MotorControllerFrontLeftAngle = DeviceTypeMotorController | MotorControllerSend | MotorControllerAngle | MotorControllerFront | MotorControllerLeft,
            MotorControllerFrontRightAngle = DeviceTypeMotorController | MotorControllerSend | MotorControllerAngle | MotorControllerFront | MotorControllerRight,
            MotorControllerBackLeftAngle = DeviceTypeMotorController | MotorControllerSend | MotorControllerAngle | MotorControllerBack | MotorControllerLeft,
            MotorControllerBackRightAngle = DeviceTypeMotorController | MotorControllerSend | MotorControllerAngle | MotorControllerBack | MotorControllerRight,

            MotorControllerFrontLeftDcPhaA = DeviceTypeMotorController | MotorControllerSend | MotorControllerDcPhaA | MotorControllerFront | MotorControllerLeft,
            MotorControllerFrontRightDcPhaA = DeviceTypeMotorController | MotorControllerSend | MotorControllerDcPhaA | MotorControllerFront | MotorControllerRight,
            MotorControllerBackLeftDcPhaA = DeviceTypeMotorController | MotorControllerSend | MotorControllerDcPhaA | MotorControllerBack | MotorControllerLeft,
            MotorControllerBackRightDcPhaA = DeviceTypeMotorController | MotorControllerSend | MotorControllerDcPhaA | MotorControllerBack | MotorControllerRight,

            MotorControllerFrontLeftDcPhaB = DeviceTypeMotorController | MotorControllerSend | MotorControllerDcPhaB | MotorControllerFront | MotorControllerLeft,
            MotorControllerFrontRightDcPhaB = DeviceTypeMotorController | MotorControllerSend | MotorControllerDcPhaB | MotorControllerFront | MotorControllerRight,
            MotorControllerBackLeftDcPhaB = DeviceTypeMotorController | MotorControllerSend | MotorControllerDcPhaB | MotorControllerBack | MotorControllerLeft,
            MotorControllerBackRightDcPhaB = DeviceTypeMotorController | MotorControllerSend | MotorControllerDcPhaB | MotorControllerBack | MotorControllerRight,

            MotorControllerFrontLeftDcPhaC = DeviceTypeMotorController | MotorControllerSend | MotorControllerDcPhaC | MotorControllerFront | MotorControllerLeft,
            MotorControllerFrontRightDcPhaC = DeviceTypeMotorController | MotorControllerSend | MotorControllerDcPhaC | MotorControllerFront | MotorControllerRight,
            MotorControllerBackLeftDcPhaC = DeviceTypeMotorController | MotorControllerSend | MotorControllerDcPhaC | MotorControllerBack | MotorControllerLeft,
            MotorControllerBackRightDcPhaC = DeviceTypeMotorController | MotorControllerSend | MotorControllerDcPhaC | MotorControllerBack | MotorControllerRight,

            MotorControllerFrontLeftChops = DeviceTypeMotorController | MotorControllerSend | MotorControllerChops | MotorControllerFront | MotorControllerLeft,
            MotorControllerFrontRightChops = DeviceTypeMotorController | MotorControllerSend | MotorControllerChops | MotorControllerFront | MotorControllerRight,
            MotorControllerBackLeftChops = DeviceTypeMotorController | MotorControllerSend | MotorControllerChops | MotorControllerBack | MotorControllerLeft,
            MotorControllerBackRightChops = DeviceTypeMotorController | MotorControllerSend | MotorControllerChops | MotorControllerBack | MotorControllerRight,

            MotorControllerFrontLeftHall = DeviceTypeMotorController | MotorControllerSend | MotorControllerHall | MotorControllerFront | MotorControllerLeft,
            MotorControllerFrontRightHall = DeviceTypeMotorController | MotorControllerSend | MotorControllerHall | MotorControllerFront | MotorControllerRight,
            MotorControllerBackLeftHall = DeviceTypeMotorController | MotorControllerSend | MotorControllerHall | MotorControllerBack | MotorControllerLeft,
            MotorControllerBackRightHall = DeviceTypeMotorController | MotorControllerSend | MotorControllerHall | MotorControllerBack | MotorControllerRight,

            MotorControllerFrontLeftVoltage = DeviceTypeMotorController | MotorControllerSend | MotorControllerVoltage | MotorControllerFront | MotorControllerLeft,
            MotorControllerFrontRightVoltage = DeviceTypeMotorController | MotorControllerSend | MotorControllerVoltage | MotorControllerFront | MotorControllerRight,
            MotorControllerBackLeftVoltage = DeviceTypeMotorController | MotorControllerSend | MotorControllerVoltage | MotorControllerBack | MotorControllerLeft,
            MotorControllerBackRightVoltage = DeviceTypeMotorController | MotorControllerSend | MotorControllerVoltage | MotorControllerBack | MotorControllerRight,

            MotorControllerFrontLeftTemp = DeviceTypeMotorController | MotorControllerSend | MotorControllerTemp | MotorControllerFront | MotorControllerLeft,
            MotorControllerFrontRightTemp = DeviceTypeMotorController | MotorControllerSend | MotorControllerTemp | MotorControllerFront | MotorControllerRight,
            MotorControllerBackLeftTemp = DeviceTypeMotorController | MotorControllerSend | MotorControllerTemp | MotorControllerBack | MotorControllerLeft,
            MotorControllerBackRightTemp = DeviceTypeMotorController | MotorControllerSend | MotorControllerTemp | MotorControllerBack | MotorControllerRight,
            };

    ESP_LOGI("CAN", "CAN MESSAGE RECEIVED OMG!!!!eins");
    ESP_LOGI("CAN", ".identifier = %u", message.identifier);
    ESP_LOGI("CAN", ".flags      = %u", message.flags);
    ESP_LOGI("CAN", ".length     = %hhu", message.data_length_code);

    switch (message.identifier)
    {
    case MotorControllerFrontLeftDcLink:
        m_lastCanFeedback = millis();
        controllers.front.feedbackValid = true;
        controllers.front.feedback.left.current = *((int16_t*)message.data);
        break;
    case MotorControllerFrontRightDcLink:
        m_lastCanFeedback = millis();
        controllers.front.feedbackValid = true;
        controllers.front.feedback.right.current = *((int16_t*)message.data);
        break;
    case MotorControllerFrontLeftSpeed:
        m_lastCanFeedback = millis();
        controllers.front.feedbackValid = true;
        controllers.front.feedback.left.speed = *((int16_t*)message.data);
        break;
    case MotorControllerFrontRightSpeed:
        m_lastCanFeedback = millis();
        controllers.front.feedbackValid = true;
        controllers.front.feedback.right.speed = *((int16_t*)message.data);
        break;
    case MotorControllerFrontLeftError:
        m_lastCanFeedback = millis();
        controllers.front.feedbackValid = true;
        controllers.front.feedback.left.error = *((int8_t*)message.data);
        break;
    case MotorControllerFrontRightError:
        m_lastCanFeedback = millis();
        controllers.front.feedbackValid = true;
        controllers.front.feedback.right.error = *((int8_t*)message.data);
        break;
    case MotorControllerFrontLeftAngle:
        m_lastCanFeedback = millis();
        controllers.front.feedbackValid = true;
        controllers.front.feedback.left.angle = *((int16_t*)message.data);
        break;
    case MotorControllerFrontRightAngle:
        m_lastCanFeedback = millis();
        controllers.front.feedbackValid = true;
        controllers.front.feedback.right.angle = *((int16_t*)message.data);
        break;
    case MotorControllerFrontLeftChops:
        m_lastCanFeedback = millis();
        controllers.front.feedbackValid = true;
        controllers.front.feedback.left.chops = *((uint16_t*)message.data);
        break;
    case MotorControllerFrontRightChops:
        m_lastCanFeedback = millis();
        controllers.front.feedbackValid = true;
        controllers.front.feedback.right.chops = *((uint16_t*)message.data);
        break;
    case MotorControllerFrontLeftVoltage:
        m_lastCanFeedback = millis();
        controllers.front.feedbackValid = true;
        controllers.front.feedback.batVoltage = *((int16_t*)message.data);
        break;
    case MotorControllerFrontLeftTemp:
        m_lastCanFeedback = millis();
        controllers.front.feedbackValid = true;
        controllers.front.feedback.boardTemp = *((int16_t*)message.data);
        break;
    }
}
}
