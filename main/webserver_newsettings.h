#pragma once

// esp-idf includes
#ifdef FEATURE_WEBSERVER
#include <esp_http_server.h>
#endif
#include <esp_err.h>

#ifdef FEATURE_WEBSERVER
esp_err_t webserver_newSettings_handler(httpd_req_t *req);
esp_err_t webserver_saveNewSettings_handler(httpd_req_t *req);
esp_err_t webserver_resetNewSettings_handler(httpd_req_t *req);
#endif
