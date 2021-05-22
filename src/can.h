#pragma once

#include <cstring>

#include <driver/gpio.h>
#include <driver/can.h>

#include <Arduino.h>

#include "bobbycar-protocol/bobbycar-can.h"

#include "types.h"
#include "globals.h"

namespace {
void initCan()
{
    Serial.println("initCan()");

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

template<bool isBack>
bool parseCanMessage(const can_message_t &message)
{
    auto &controller = isBack ? controllers.back : controllers.front;

    switch (message.identifier)
    {
    using namespace bobbycar::can;
    case MotorController<isBack, false>::Feedback::DcLink:
        controller.feedback.left.current = *((int16_t*)message.data);
        return true;
    case MotorController<isBack, true>::Feedback::DcLink:
        controller.feedback.right.current = *((int16_t*)message.data);
        return true;
    case MotorController<isBack, false>::Feedback::Speed:
        controller.feedback.left.speed = *((int16_t*)message.data);
        return true;
    case MotorController<isBack, true>::Feedback::Speed:
        controller.feedback.right.speed = *((int16_t*)message.data);
        return true;
    case MotorController<isBack, false>::Feedback::Error:
        controller.feedback.left.error = *((int8_t*)message.data);
        return true;
    case MotorController<isBack, true>::Feedback::Error:
        controller.feedback.right.error = *((int8_t*)message.data);
        return true;
    case MotorController<isBack, false>::Feedback::Angle:
        controller.feedback.left.angle = *((int16_t*)message.data);
        return true;
    case MotorController<isBack, true>::Feedback::Angle:
        controller.feedback.right.angle = *((int16_t*)message.data);
        return true;
    case MotorController<isBack, false>::Feedback::DcPhaA:
    case MotorController<isBack, true>::Feedback::DcPhaA:
    case MotorController<isBack, false>::Feedback::DcPhaB:
    case MotorController<isBack, true>::Feedback::DcPhaB:
    case MotorController<isBack, false>::Feedback::DcPhaC:
    case MotorController<isBack, true>::Feedback::DcPhaC:
        return true;
    case MotorController<isBack, false>::Feedback::Chops:
        controller.feedback.left.chops = *((uint16_t*)message.data);
        return true;
    case MotorController<isBack, true>::Feedback::Chops:
        controller.feedback.right.chops = *((uint16_t*)message.data);
        return true;
    case MotorController<isBack, false>::Feedback::Hall:
        controller.feedback.left.hallA = *((uint8_t*)message.data) & 1;
        controller.feedback.left.hallB = *((uint8_t*)message.data) & 2;
        controller.feedback.left.hallC = *((uint8_t*)message.data) & 4;
        return true;
    case MotorController<isBack, true>::Feedback::Hall:
        controller.feedback.right.hallA = *((uint8_t*)message.data) & 1;
        controller.feedback.right.hallB = *((uint8_t*)message.data) & 2;
        controller.feedback.right.hallC = *((uint8_t*)message.data) & 4;
        return true;
    case MotorController<isBack, false>::Feedback::Voltage:
    case MotorController<isBack, true>::Feedback::Voltage:
        controller.feedback.batVoltage = *((int16_t*)message.data);
        return true;
    case MotorController<isBack, false>::Feedback::Temp:
    case MotorController<isBack, true>::Feedback::Temp:
        controller.feedback.boardTemp = *((int16_t*)message.data);
        return true;
    }

    return false;
}

bool parseCanInput()
{
    can_message_t message;
    if (const auto result = can_receive(&message, pdMS_TO_TICKS(50)); result != ESP_OK)
    {
        if (millis() - controllers.front.lastCanFeedback > 100)
            controllers.front.feedbackValid = false;

        if (millis() - controllers.back.lastCanFeedback > 100)
            controllers.back.feedbackValid = false;

        if (result != ESP_ERR_TIMEOUT)
            Serial.printf("CAN err can_receive() failed with %s\r\n", esp_err_to_name(result));

        return false;
    }

    if (parseCanMessage<false>(message))
    {
        if (millis() - controllers.back.lastCanFeedback > 100)
            controllers.back.feedbackValid = false;

        controllers.front.lastCanFeedback = millis();
        controllers.front.feedbackValid = true;
        return true;
    }
    else
    {
        if (millis() - controllers.front.lastCanFeedback > 100)
            controllers.front.feedbackValid = false;
    }

    if (parseCanMessage<true>(message))
    {
        controllers.back.lastCanFeedback = millis();
        controllers.back.feedbackValid = true;
        return true;
    }
    else
    {
        if (millis() - controllers.back.lastCanFeedback > 100)
            controllers.back.feedbackValid = false;
    }

    //Serial.printf("WARNING Unknown CAN info received .identifier = %u\r\n", message.identifier);

    return true;
}

void sendCanCommands()
{
    constexpr auto send = [](uint32_t addr, auto value){
        can_message_t message;
        message.identifier = addr;
        message.flags = CAN_MSG_FLAG_SS;
        message.data_length_code = sizeof(value);
        std::fill(std::begin(message.data), std::end(message.data), 0);
        std::memcpy(message.data, &value, sizeof(value));

        const auto result = can_transmit(&message, pdMS_TO_TICKS(200));
        if (result != ESP_OK && result != ESP_ERR_TIMEOUT)
            Serial.printf("ERROR: can_transmit() failed with %s\r\n", esp_err_to_name(result));
        return result;
    };

    using namespace bobbycar::can;

    send(MotorController<false, false>::Command::InpTgt, controllers.front.command.left.pwm);
    send(MotorController<false, true>::Command::InpTgt, controllers.front.command.right.pwm);
    send(MotorController<true, false>::Command::InpTgt, controllers.back.command.left.pwm);
    send(MotorController<true, true>::Command::InpTgt, controllers.back.command.right.pwm);

    static int i{};
    switch (i++)
    {
    case 0:
        send(MotorController<false, false>::Command::Enable, controllers.front.command.left.enable);
        send(MotorController<false, true>::Command::Enable, controllers.front.command.right.enable);
        send(MotorController<true, false>::Command::Enable, controllers.back.command.left.enable);
        send(MotorController<true, true>::Command::Enable, controllers.back.command.right.enable);
        break;
    case 1:
        send(MotorController<false, false>::Command::CtrlTyp, controllers.front.command.left.ctrlTyp);
        send(MotorController<false, true>::Command::CtrlTyp, controllers.front.command.right.ctrlTyp);
        send(MotorController<true, false>::Command::CtrlTyp, controllers.back.command.left.ctrlTyp);
        send(MotorController<true, true>::Command::CtrlTyp, controllers.back.command.right.ctrlTyp);
        break;
    case 2:
        send(MotorController<false, false>::Command::CtrlMod, controllers.front.command.left.ctrlMod);
        send(MotorController<false, true>::Command::CtrlMod, controllers.front.command.right.ctrlMod);
        send(MotorController<true, false>::Command::CtrlMod, controllers.back.command.left.ctrlMod);
        send(MotorController<true, true>::Command::CtrlMod, controllers.back.command.right.ctrlMod);
        break;
    case 3:
        send(MotorController<false, false>::Command::IMotMax, controllers.front.command.left.iMotMax);
        send(MotorController<false, true>::Command::IMotMax, controllers.front.command.right.iMotMax);
        send(MotorController<true, false>::Command::IMotMax, controllers.back.command.left.iMotMax);
        send(MotorController<true, true>::Command::IMotMax, controllers.back.command.right.iMotMax);
        break;
    case 4:
        send(MotorController<false, false>::Command::IDcMax, controllers.front.command.left.iDcMax);
        send(MotorController<false, true>::Command::IDcMax, controllers.front.command.right.iDcMax);
        send(MotorController<true, false>::Command::IDcMax, controllers.back.command.left.iDcMax);
        send(MotorController<true, true>::Command::IDcMax, controllers.back.command.right.iDcMax);
        break;
    case 5:
        send(MotorController<false, false>::Command::NMotMax, controllers.front.command.left.nMotMax);
        send(MotorController<false, true>::Command::NMotMax, controllers.front.command.right.nMotMax);
        send(MotorController<true, false>::Command::NMotMax, controllers.back.command.left.nMotMax);
        send(MotorController<true, true>::Command::NMotMax, controllers.back.command.right.nMotMax);
        break;
    case 6:
        send(MotorController<false, false>::Command::FieldWeakMax, controllers.front.command.left.fieldWeakMax);
        send(MotorController<false, true>::Command::FieldWeakMax, controllers.front.command.right.fieldWeakMax);
        send(MotorController<true, false>::Command::FieldWeakMax, controllers.back.command.left.fieldWeakMax);
        send(MotorController<true, true>::Command::FieldWeakMax, controllers.back.command.right.fieldWeakMax);
        break;
    case 7:
        send(MotorController<false, false>::Command::PhaseAdvMax, controllers.front.command.left.phaseAdvMax);
        send(MotorController<false, true>::Command::PhaseAdvMax, controllers.front.command.right.phaseAdvMax);
        send(MotorController<true, false>::Command::PhaseAdvMax, controllers.back.command.left.phaseAdvMax);
        send(MotorController<true, true>::Command::PhaseAdvMax, controllers.back.command.right.phaseAdvMax);
        break;
    case 8:
        send(MotorController<false, false>::Command::BuzzerFreq, controllers.front.command.buzzer.freq);
        send(MotorController<false, true>::Command::BuzzerFreq, controllers.front.command.buzzer.freq);
        send(MotorController<true, false>::Command::BuzzerFreq, controllers.back.command.buzzer.freq);
        send(MotorController<true, true>::Command::BuzzerFreq, controllers.back.command.buzzer.freq);
        break;
    case 9:
        send(MotorController<false, false>::Command::BuzzerPattern, controllers.front.command.buzzer.pattern);
        send(MotorController<false, true>::Command::BuzzerPattern, controllers.front.command.buzzer.pattern);
        send(MotorController<true, false>::Command::BuzzerPattern, controllers.back.command.buzzer.pattern);
        send(MotorController<true, true>::Command::BuzzerPattern, controllers.back.command.buzzer.pattern);
        break;
    case 10:
        send(MotorController<false, false>::Command::Led, controllers.front.command.led);
        send(MotorController<false, true>::Command::Led, controllers.front.command.led);
        send(MotorController<true, false>::Command::Led, controllers.back.command.led);
        send(MotorController<true, true>::Command::Led, controllers.back.command.led);
        break;
    case 11:
        send(MotorController<false, false>::Command::Poweroff, controllers.front.command.poweroff);
        send(MotorController<false, true>::Command::Poweroff, controllers.front.command.poweroff);
        send(MotorController<true, false>::Command::Poweroff, controllers.back.command.poweroff);
        send(MotorController<true, true>::Command::Poweroff, controllers.back.command.poweroff);
        i=0;
        break;
    }
}
}
