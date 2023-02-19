#pragma once

// esp-idf includes
#include <esp_http_server.h>
#include <esp_err.h>

namespace bobby::webserver {

esp_err_t webserver_dump_nvs_handler(httpd_req_t *req);

} // namespace bobby::webserver
