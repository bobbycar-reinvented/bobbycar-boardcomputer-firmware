#pragma once

// system includes
#include <atomic>
#include <string_view>

// esp-idf includes
#ifdef FEATURE_WEBSERVER
#include <esp_http_server.h>
#endif
#include <esp_log.h>

// 3rdparty lib includes
#include <espcppmacros.h>
#include <esphttpdutils.h>

// local includes
#include "webserver_lock.h"
#include "webserver_displaycontrol.h"
#ifdef FEATURE_OTA
#include "webserver_ota.h"
#endif
#include "webserver_settings.h"
#include "webserver_stringsettings.h"
#ifdef OLD_NVS
#include "webserver_dumpnvs.h"
#endif

#ifdef FEATURE_WEBSERVER
extern httpd_handle_t httpdHandle;

void initWebserver();
void handleWebserver();
esp_err_t webserver_reboot_handler(httpd_req_t *req);
#endif
