#pragma once

// esp-idf includes
#include <esp_http_server.h>

namespace bobby::webserver {

extern httpd_handle_t httpdHandle;

void initWebserver();
void handleWebserver();
bool MenuDisplayChanged();

} // namespace bobby::webserver
