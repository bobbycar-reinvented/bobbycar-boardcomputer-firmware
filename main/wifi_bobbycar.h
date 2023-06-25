#pragma once

// system includes
#include <optional>

// esp-idf includes
#include <esp_err.h>

// 3rdparty lib includes
#include <espwifiutils.h>

void wifi_begin();

void wifi_update();

esp_err_t wifi_scan();

void set_ap_channel_override(uint8_t channel);

void disable_ap_channel_override();

std::optional<uint8_t>& get_ap_channel_override();
