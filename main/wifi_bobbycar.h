#pragma once

// esp-idf includes
#include <esp_err.h>

// 3rdparty lib includes
#include <espwifiutils.h>

constexpr const wifi_stack::ip_address_t apIP{10, 0, 0, 1};
constexpr const wifi_stack::ip_address_t netMsk{255, 255, 255, 0};

void wifi_begin();

void wifi_update();

esp_err_t wifi_scan();
