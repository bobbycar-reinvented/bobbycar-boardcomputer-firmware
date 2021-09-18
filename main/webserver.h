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
#include "webserver_displaycontrol.h"
#ifdef FEATURE_OTA
#include "webserver_ota.h"
#endif
#include "webserver_settings.h"

#ifdef FEATURE_WEBSERVER
namespace {
httpd_handle_t httpdHandle;

std::atomic<bool> shouldReboot;

void initWebserver();
void handleWebserver();
esp_err_t webserver_reboot_handler(httpd_req_t *req);
}

namespace {
void initWebserver()
{
    shouldReboot = false;

    {
        httpd_config_t httpConfig HTTPD_DEFAULT_CONFIG();
        httpConfig.core_id = 1;
        httpConfig.max_uri_handlers = 14;

        const auto result = httpd_start(&httpdHandle, &httpConfig);
        ESP_LOG_LEVEL_LOCAL((result == ESP_OK ? ESP_LOG_INFO : ESP_LOG_ERROR), TAG, "httpd_start(): %s", esp_err_to_name(result));
        if (result != ESP_OK)
            return;
    }

    for (const httpd_uri_t &uri : {
         httpd_uri_t { .uri = "/",              .method = HTTP_GET, .handler = webserver_root_handler,          .user_ctx = NULL },
         httpd_uri_t { .uri = "/triggerButton", .method = HTTP_GET, .handler = webserver_triggerButton_handler, .user_ctx = NULL },
         httpd_uri_t { .uri = "/triggerItem",   .method = HTTP_GET, .handler = webserver_triggerItem_handler,   .user_ctx = NULL },
         httpd_uri_t { .uri = "/setValue",      .method = HTTP_GET, .handler = webserver_setValue_handler,      .user_ctx = NULL },
         httpd_uri_t { .uri = "/reboot",        .method = HTTP_GET, .handler = webserver_reboot_handler,        .user_ctx = NULL },
#ifdef FEATURE_OTA
         httpd_uri_t { .uri = "/ota",           .method = HTTP_GET, .handler = webserver_ota_handler,           .user_ctx = NULL },
         httpd_uri_t { .uri = "/triggerOta",    .method = HTTP_GET, .handler = webserver_trigger_ota_handler,   .user_ctx = NULL },
#endif
         httpd_uri_t { .uri = "/settings",      .method = HTTP_GET, .handler = webserver_settings_handler,      .user_ctx = NULL },
         httpd_uri_t { .uri = "/saveSettings",  .method = HTTP_GET, .handler = webserver_save_settings_handler, .user_ctx = NULL },
    })
    {
        const auto result = httpd_register_uri_handler(httpdHandle, &uri);
        ESP_LOG_LEVEL_LOCAL((result == ESP_OK ? ESP_LOG_INFO : ESP_LOG_ERROR), TAG, "httpd_register_uri_handler() for %s: %s", uri.uri, esp_err_to_name(result));
        //if (result != ESP_OK)
        //    return result;
    }
}

void handleWebserver()
{
    if (shouldReboot)
    {
        shouldReboot = false;
        esp_restart();
    }
}

esp_err_t webserver_reboot_handler(httpd_req_t *req)
{
    shouldReboot = true;

    CALL_AND_EXIT(esphttpdutils::webserver_resp_send, req, esphttpdutils::ResponseStatus::Ok, "text/plain", "REBOOT called...")
}

}
#endif
