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

            stringSettings.executeForEveryCommonSetting([&](const char *key, auto value){
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
    CALL_AND_EXIT(esphttpdutils::webserver_resp_send, req, esphttpdutils::ResponseStatus::Ok, "text/plain", "not yet implemented")
}
} // namespace

#endif

