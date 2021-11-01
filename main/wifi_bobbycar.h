#pragma once

// esp-idf includes
#include <esp_err.h>

void wifi_begin();

void wifi_update();

esp_err_t wifi_scan();
