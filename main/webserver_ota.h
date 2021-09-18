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
#ifdef FEATURE_OTA
#include "ota.h"
#endif

#if defined(FEATURE_WEBSERVER) && defined(FEATURE_OTA)
namespace {
esp_err_t webserver_ota_handler(httpd_req_t *req);
esp_err_t webserver_trigger_ota_handler(httpd_req_t *req);
} // namespace

using esphttpdutils::HtmlTag;

namespace {
esp_err_t webserver_ota_handler(httpd_req_t *req)
{
    std::string body;

    {
        HtmlTag htmlTag{"html", body};

        {
            HtmlTag headTag{"head", body};

            {
                HtmlTag titleTag{"title", body};
                body += "Update";
            }

            body += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1, shrink-to-fit=no\" />";
        }

        {
            HtmlTag bodyTag{"body", body};

            {
                HtmlTag h1Tag{"h1", body};
                body += "Update";
            }

            {
                HtmlTag pTag{"p", body};
                body += "<a href=\"/\">Display control</a> "
                        "<b>Update</b> "
                        "<a href=\"/settings\">Settings</a>";
            }

            {
                HtmlTag formTag{"form", "action=\"/triggerOta\" method=\"GET\"", body};
                HtmlTag fieldsetTag{"fieldset", body};
                {
                    HtmlTag legendTag{"legend", body};
                    body += "Trigger Update";
                }

                body += fmt::format("<input type=\"text\" name=\"url\" value=\"{}\" required />", esphttpdutils::htmlentities(stringSettings.otaUrl));

                {
                    HtmlTag buttonTag{"button", "type=\"submit\"", body};
                    body += "Go";
                }
            }
        }
    }

    CALL_AND_EXIT(esphttpdutils::webserver_resp_send, req, esphttpdutils::ResponseStatus::Ok, "text/html", body)
}

esp_err_t webserver_trigger_ota_handler(httpd_req_t *req)
{
    CALL_AND_EXIT(esphttpdutils::webserver_resp_send, req, esphttpdutils::ResponseStatus::Ok, "text/plain", "not yet implemented")
}
}
#endif
