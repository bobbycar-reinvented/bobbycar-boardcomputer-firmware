#pragma once

// esp-idf includes
#include <esp_log.h>

// 3rdparty lib includes
#include <wrappers/websocket_client.h>
#include <espwifistack.h>
#include <esphttpdutils.h>

// local includes
#include "globals.h"

namespace {
#ifdef FEATURE_CLOUD
espcpputils::websocket_client cloudClient;
bool cloudStarted{};
espchrono::millis_clock::time_point lastCreateTry;
espchrono::millis_clock::time_point lastStartTry;

void createCloud();
void destroyCloud();
void startCloud();

void initCloud()
{
    if (settings.cloudSettings.cloudEnabled &&
        !stringSettings.cloudUrl.empty() &&
        esphttpdutils::urlverify(stringSettings.cloudUrl))
    {
        createCloud();
        if (!cloudClient)
            return;

        if (wifi_stack::get_sta_status() != wifi_stack::WiFiStaStatus::CONNECTED)
            return;

        startCloud();
    }
}

void handleCloud()
{
    if (settings.cloudSettings.cloudEnabled &&
        !stringSettings.cloudUrl.empty() &&
        esphttpdutils::urlverify(stringSettings.cloudUrl))
    {
        if (!cloudClient)
        {
            if (espchrono::ago(lastCreateTry) < 10s)
                return;
            createCloud();
        }
        if (!cloudClient)
            return;

        if (!cloudStarted)
        {
            if (espchrono::ago(lastStartTry) < 10s)
                return;

            if (wifi_stack::get_sta_status() != wifi_stack::WiFiStaStatus::CONNECTED)
                return;

            startCloud();
        }
        if (!cloudStarted)
            return;

        if (!cloudClient.is_connected())
            return;

        std::string rssi = "null";
        if (wifi_stack::get_sta_status() == wifi_stack::WiFiStaStatus::CONNECTED)
            if (const auto &result = wifi_stack::get_sta_ap_info(); result)
                rssi = std::to_string(result->rssi);

        std::string msg = "{"
            "\"type\": \"fullStatus\","
            "\"partial\": false, "
            "\"status\": {"
                "\"millis\":" + std::to_string(std::chrono::milliseconds{espchrono::millis_clock::now().time_since_epoch()}.count()) + ","
                "\"rssi\":" + rssi + ","
                "\"front.valid\":" + std::to_string(controllers.front.feedbackValid) + ","
                "\"back.valid\":" + std::to_string(controllers.back.feedbackValid) + ","
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
                "\"front.left.current\":" + std::to_string(controllers.front.feedback.left.dcLink) + ","
                "\"front.right.current\":" + std::to_string(controllers.front.feedback.right.dcLink) + ","
                "\"back.left.current\":" + std::to_string(controllers.back.feedback.left.dcLink) + ","
                "\"back.right.current\":" + std::to_string(controllers.back.feedback.right.dcLink) + ","
                "\"front.left.error\":" + std::to_string(controllers.front.feedback.left.error) + ","
                "\"front.right.error\":" + std::to_string(controllers.front.feedback.right.error) + ","
                "\"back.left.error\":" + std::to_string(controllers.back.feedback.left.error) + ","
                "\"back.right.error\":" + std::to_string(controllers.back.feedback.right.error) +
            "}"
        "}";

        const auto timeout = std::chrono::ceil<espcpputils::ticks>(espchrono::milliseconds32{settings.cloudSettings.cloudTransmitTimeout}).count();
        const auto written = cloudClient.send_text(msg, timeout);

        if (written < 0)
        {
            ESP_LOGE("BOBBY", "cloudClient.send_text() failed with %i", written);
        }
        else if (written != msg.size())
        {
            ESP_LOGE("BOBBY", "websocket sent size mismatch, sent=%i, expected=%i", written, msg.size());
        }
    }
    else if (cloudClient)
    {
        destroyCloud();
    }
}

void createCloud()
{
    ESP_LOGI("BOBBY", "called");

    if (cloudClient)
    {
        ESP_LOGE(TAG, "cloud client already created");
        return;
    }

    lastCreateTry = espchrono::millis_clock::now();

    const esp_websocket_client_config_t config = {
        .uri = stringSettings.cloudUrl.c_str(),
    };

    cloudClient = espcpputils::websocket_client{&config};

    if (!cloudClient)
    {
        ESP_LOGE(TAG, "websocket could not be constructed");
        return;
    }

    ESP_LOGI("BOBBY", "cloud client created");
}

void startCloud()
{
    ESP_LOGI("BOBBY", "called");

    if (!cloudClient)
    {
        ESP_LOGE(TAG, "cloud client not created");
        return;
    }

    if (cloudStarted)
    {
        ESP_LOGE(TAG, "cloud client already started");
        return;
    }

    lastStartTry = espchrono::millis_clock::now();

    const auto result = cloudClient.start();
    ESP_LOG_LEVEL_LOCAL((result == ESP_OK ? ESP_LOG_INFO : ESP_LOG_ERROR), "BOBBY", "cloudClient.start() returned: %s", esp_err_to_name(result));

    if (result == ESP_OK)
        cloudStarted = true;
}

void destroyCloud()
{
    ESP_LOGI("BOBBY", "called");

    if (!cloudClient)
    {
        ESP_LOGE(TAG, "cloud client not created");
        return;
    }

    cloudClient = {};
    cloudStarted = false;
}
#endif
} // namespace
