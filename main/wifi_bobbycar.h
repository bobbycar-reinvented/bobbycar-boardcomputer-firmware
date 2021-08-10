#pragma once

// esp-idf includes
#include <esp_log.h>

// 3rdparty lib includes
#include <espwifistack.h>

// local includes
#include "globals.h"

namespace {
wifi_stack::config wifi_create_config()
{
    return wifi_stack::config {
        .wifiEnabled = settings.wifiSettings.wifiEnabled,
        .hostname = deviceName,
        .sta = {
            .wifis = std::array<wifi_stack::wifi_entry, 10> {
                wifi_stack::wifi_entry { .ssid = stringSettings.wifis[0].ssid, .key = stringSettings.wifis[0].key },
                wifi_stack::wifi_entry { .ssid = stringSettings.wifis[1].ssid, .key = stringSettings.wifis[1].key },
                wifi_stack::wifi_entry { .ssid = stringSettings.wifis[2].ssid, .key = stringSettings.wifis[2].key },
                wifi_stack::wifi_entry { .ssid = stringSettings.wifis[3].ssid, .key = stringSettings.wifis[3].key },
                wifi_stack::wifi_entry { .ssid = stringSettings.wifis[4].ssid, .key = stringSettings.wifis[4].key },
                wifi_stack::wifi_entry { .ssid = stringSettings.wifis[5].ssid, .key = stringSettings.wifis[5].key },
                wifi_stack::wifi_entry { .ssid = stringSettings.wifis[6].ssid, .key = stringSettings.wifis[6].key },
                wifi_stack::wifi_entry { .ssid = stringSettings.wifis[7].ssid, .key = stringSettings.wifis[7].key },
                wifi_stack::wifi_entry { .ssid = stringSettings.wifis[8].ssid, .key = stringSettings.wifis[8].key },
                wifi_stack::wifi_entry { .ssid = stringSettings.wifis[9].ssid, .key = stringSettings.wifis[9].key }
            },
            .min_rssi = -90
        },
        .ap = {
            .ssid = deviceName,
            .key = STRING(AP_PASSWORD),
            .static_ip = {
                .ip = {10, 0, 0, 1},
                .subnet = {255, 255, 255, 0},
                .gateway = {10, 0, 0, 1},
            },
            .channel = 1,
            .authmode = WIFI_AUTH_WPA2_PSK,
            .ssid_hidden = false,
            .max_connection = 4,
            .beacon_interval = 100
        }
    };
}

void wifi_begin()
{
    wifi_stack::init(wifi_create_config());
}

void wifi_update()
{
    wifi_stack::update(wifi_create_config());
}

esp_err_t wifi_scan()
{
    if (const auto result = wifi_stack::begin_scan(wifi_create_config()); result != ESP_OK)
    {
        ESP_LOGE("BOBBY", "begin_scan() failed with %s", esp_err_to_name(result));
        return result;
    }

    return ESP_OK;
}
} // namespace
