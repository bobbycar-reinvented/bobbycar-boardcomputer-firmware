#pragma once

// esp-idf includes
#ifdef FEATURE_WEBSERVER
#include <esp_http_server.h>
#endif
#include <esp_log.h>

// 3rdparty lib includes
#include <htmlbuilder.h>
#include <fmt/core.h>
#include <espcppmacros.h>
#include <esphttpdutils.h>

// local includes
#include "globals.h"

#ifdef FEATURE_WEBSERVER
namespace {
esp_err_t webserver_settings_handler(httpd_req_t *req);
esp_err_t webserver_save_settings_handler(httpd_req_t *req);
} // namespace

using esphttpdutils::HtmlTag;

namespace {
esp_err_t webserver_settings_handler(httpd_req_t *req)
{
    std::string body;

    {
        HtmlTag htmlTag{"html", body};

        {
            HtmlTag headTag{"head", body};

            {
                HtmlTag titleTag{"title", body};
                body += "Settings";
            }

            body += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1, shrink-to-fit=no\" />";
        }

        {
            HtmlTag bodyTag{"body", body};

            {
                HtmlTag h1Tag{"h1", body};
                body += "Settings";
            }

            {
                HtmlTag pTag{"p", body};
                body += "<a href=\"/\">Display control</a> "
#ifdef FEATURE_OTA
                        "<a href=\"/ota\">Update</a> "
#endif
                        "<b>Settings</b>";
            }

            stringSettings.executeForEveryCommonSetting([&](const char *key, const auto &value){
                HtmlTag formTag{"form", "action=\"/saveSettings\" method=\"GET\"", body};
                HtmlTag fieldsetTag{"fieldset", body};
                {
                    HtmlTag legendTag{"legend", body};
                    body += esphttpdutils::htmlentities(key);
                }

                body += fmt::format("<input type=\"text\" name=\"{}\" value=\"{}\" required />",
                                    esphttpdutils::htmlentities(key),
                                    esphttpdutils::htmlentities(value));

                {
                    HtmlTag buttonTag{"button", "type=\"submit\"", body};
                    body += "Save";
                }
            });
        }
    }

    CALL_AND_EXIT(esphttpdutils::webserver_resp_send, req, esphttpdutils::ResponseStatus::Ok, "text/html", body)
}

esp_err_t webserver_save_settings_handler(httpd_req_t *req)
{
    std::string query;
    if (auto result = esphttpdutils::webserver_get_query(req))
        query = *result;
    else
    {
        ESP_LOGE(TAG, "%.*s", result.error().size(), result.error().data());
        CALL_AND_EXIT(esphttpdutils::webserver_resp_send, req, esphttpdutils::ResponseStatus::BadRequest, "text/plain", result.error());
    }

    std::string body;
    bool success{true};

    stringSettings.executeForEveryCommonSetting([&](const char *key, auto &value){
        char valueBufEncoded[256];
        if (const auto result = httpd_query_key_value(query.data(), key, valueBufEncoded, 256); result != ESP_OK && result != ESP_ERR_NOT_FOUND)
        {
            const auto msg = fmt::format("{}: httpd_query_key_value() failed with {}", key, esp_err_to_name(result));
            ESP_LOGE(TAG, "%.*s", msg.size(), msg.data());
            body += msg;
            body += '\n';
            success = false;
            return;
        }

        char valueBuf[257];
        esphttpdutils::urldecode(valueBuf, valueBufEncoded);

        value = valueBuf;
        body += fmt::format("{}: applied", key);
        body += '\n';
    });

    if (body.empty())
        CALL_AND_EXIT(esphttpdutils::webserver_resp_send, req, esphttpdutils::ResponseStatus::Ok, "text/plain", "nothing changed?!")

    if (settingsPersister.save(stringSettings))
        body += "settings persisted successfully";
    else
    {
        body += "error while persisting settings";
        success = false;
    }

    if (success)
        CALL_AND_EXIT_ON_ERROR(httpd_resp_set_hdr, req, "Location", "/")

    CALL_AND_EXIT(esphttpdutils::webserver_resp_send,
                  req,
                  success ? esphttpdutils::ResponseStatus::TemporaryRedirect : esphttpdutils::ResponseStatus::BadRequest,
                  "text/plain",
                  body)
}
} // namespace

#endif

