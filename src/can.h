#pragma once

#include <esp_log.h>
#include <driver/gpio.h>
#include <driver/can.h>

#include <Arduino.h>

#include "bobbycar-protocol/bobbycar-can.h"

#include "types.h"
#include "globals.h"

namespace {
millis_t m_lastCanFeedback{};

void initCan()
{
    Serial.printf("CAN info hello world\r\n");

    can_general_config_t g_config = CAN_GENERAL_CONFIG_DEFAULT(GPIO_NUM_21, GPIO_NUM_22, CAN_MODE_NORMAL);
    can_timing_config_t t_config CAN_TIMING_CONFIG_250KBITS();
    can_filter_config_t f_config CAN_FILTER_CONFIG_ACCEPT_ALL();
//    {
//                           //
//        .acceptance_code = 0b00000000000,
//        .acceptance_mask = 0b00001111111,
//        .single_filter = true
//    };

    if (const auto result = can_driver_install(&g_config, &t_config, &f_config); result == ESP_OK)
    {
        Serial.printf("CAN info can_driver_install() succeeded\r\n");
    }
    else
    {
        Serial.printf("CAN err can_driver_install() failed with %s\r\n", esp_err_to_name(result));
        return;
    }

    if (const auto result = can_start(); result == ESP_OK)
    {
        Serial.printf("CAN info can_start() succeeded\r\n");
    }
    else
    {
        Serial.printf("CAN err can_start() failed with %s\r\n", esp_err_to_name(result));

        if (const auto result = can_driver_uninstall(); result == ESP_OK)
        {
            Serial.printf("CAN info can_driver_uninstall() succeeded\r\n");
        }
        else
        {
            Serial.printf("CAN err can_driver_uninstall() failed with %s\r\n", esp_err_to_name(result));
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
            Serial.printf("CAN err can_receive() failed with %s\r\n", esp_err_to_name(result));
        return;
    }

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
    case MotorControllerFrontLeftHall:
    {
        m_lastCanFeedback = millis();
        controllers.front.feedbackValid = true;
        controllers.front.feedback.left.hallA = *((uint8_t*)message.data) & 1;
        controllers.front.feedback.left.hallB = *((uint8_t*)message.data) & 2;
        controllers.front.feedback.left.hallC = *((uint8_t*)message.data) & 4;
        break;
    }
    case MotorControllerFrontRightHall:
    {
        m_lastCanFeedback = millis();
        controllers.front.feedbackValid = true;
        controllers.front.feedback.right.hallA = *((uint8_t*)message.data) & 1;
        controllers.front.feedback.right.hallB = *((uint8_t*)message.data) & 2;
        controllers.front.feedback.right.hallC = *((uint8_t*)message.data) & 4;
        break;
    }
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
    default:
        Serial.printf("WARNING Unknown CAN info received .identifier = %u\r\n", message.identifier);
    }
}
}
