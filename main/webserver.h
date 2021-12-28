#pragma once

// esp-idf includes
#ifdef FEATURE_WEBSERVER
#include <esp_http_server.h>
#endif

#ifdef FEATURE_WEBSERVER
extern httpd_handle_t httpdHandle;

void initWebserver();
void handleWebserver();
bool MenuDisplayChanged();
#endif
