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
#include <lockhelper.h>
#include <tickchrono.h>

// local includes
#ifdef FEATURE_OTA
#include "ota.h"
#endif
#include "webserver_lock.h"

#if defined(FEATURE_WEBSERVER) && defined(FEATURE_OTA)
namespace {
esp_err_t webserver_ota_handler(httpd_req_t *req);
esp_err_t webserver_trigger_ota_handler(httpd_req_t *req);
} // namespace

using esphttpdutils::HtmlTag;

namespace {
esp_err_t webserver_ota_handler(httpd_req_t *req)
{
    espcpputils::LockHelper helper{webserver_lock->handle, std::chrono::ceil<espcpputils::ticks>(5s).count()};
    if (!helper.locked())
    {
        constexpr const std::string_view msg = "could not lock webserver_lock";
        ESP_LOGE(TAG, "%.*s", msg.size(), msg.data());
        CALL_AND_EXIT(esphttpdutils::webserver_resp_send, req, esphttpdutils::ResponseStatus::BadRequest, "text/plain", msg);
    }

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
                body += "<a href=\"/\">Display control</a> - "
                        "<b>Update</b> - "
                        "<a href=\"/settings\">Settings</a> - "
                        "<a href=\"/stringSettings\">String Settings</a>";
            }

            if (const esp_app_desc_t *app_desc = esp_ota_get_app_description())
            {
                HtmlTag tableTag{"table", "border=\"1\"", body};

                {
                    HtmlTag trTag{"tr", body};
                    { HtmlTag tdTag{"td", body}; body += "Current project_name"; }
                    { HtmlTag tdTag{"td", body}; body += esphttpdutils::htmlentities(app_desc->project_name); }
                }

                {
                    HtmlTag trTag{"tr", body};
                    { HtmlTag tdTag{"td", body}; body += "Current version"; }
                    { HtmlTag tdTag{"td", body}; body += esphttpdutils::htmlentities(app_desc->version); }
                }

                {
                    HtmlTag trTag{"tr", body};
                    { HtmlTag tdTag{"td", body}; body += "Current secure_version"; }
                    { HtmlTag tdTag{"td", body}; body += std::to_string(app_desc->secure_version); }
                }

                {
                    HtmlTag trTag{"tr", body};
                    { HtmlTag tdTag{"td", body}; body += "Current timestamp"; }
                    { HtmlTag tdTag{"td", body}; body += esphttpdutils::htmlentities(fmt::format("{} {}", app_desc->date, app_desc->time)); }
                }

                {
                    HtmlTag trTag{"tr", body};
                    { HtmlTag tdTag{"td", body}; body += "Current idf_ver"; }
                    { HtmlTag tdTag{"td", body}; body += esphttpdutils::htmlentities(app_desc->idf_ver); }
                }

                {
                    HtmlTag trTag{"tr", body};
                    { HtmlTag tdTag{"td", body}; body += "Current sha256"; }
                    { HtmlTag tdTag{"td", body}; body += esphttpdutils::htmlentities(espcpputils::toHexString({app_desc->app_elf_sha256, 8})); }
                }
            }
            else
            {
                constexpr const std::string_view msg = "esp_ota_get_app_description() failed";
                ESP_LOGE(TAG, "%.*s", msg.size(), msg.data());
                HtmlTag pTag{"p", "style=\"color: red;\"", body};
                body += esphttpdutils::htmlentities(msg);
            }

            if (asyncOta)
            {
                HtmlTag tableTag{"table", "border=\"1\"", body};

                {
                    HtmlTag trTag{"tr", body};
                    { HtmlTag tdTag{"td", body}; body += "Update status"; }
                    { HtmlTag tdTag{"td", body}; body += esphttpdutils::htmlentities(toString(asyncOta->status())); }
                }

                {
                    HtmlTag trTag{"tr", body};
                    { HtmlTag tdTag{"td", body}; body += "Update progress"; }
                    {
                        HtmlTag tdTag{"td", body};
                        const auto progress = asyncOta->progress();
                        const auto totalSize = asyncOta->totalSize();
                        body += fmt::format("{} / {}{}",
                                            progress,
                                            totalSize ? std::to_string(*totalSize) : "?",
                                            (totalSize && *totalSize > 0) ? fmt::format(" ({:.02f}%)", float(progress) / *totalSize * 100) : "");
                    }
                }

                {
                    HtmlTag trTag{"tr", body};
                    { HtmlTag tdTag{"td", body}; body += "Update message"; }
                    { HtmlTag tdTag{"td", body}; body += esphttpdutils::htmlentities(asyncOta->message()); }
                }

                if (const auto &appDesc = asyncOta->appDesc())
                {
                    {
                        HtmlTag trTag{"tr", body};
                        { HtmlTag tdTag{"td", body}; body += "New project_name"; }
                        { HtmlTag tdTag{"td", body}; body += esphttpdutils::htmlentities(appDesc->project_name); }
                    }

                    {
                        HtmlTag trTag{"tr", body};
                        { HtmlTag tdTag{"td", body}; body += "New version"; }
                        { HtmlTag tdTag{"td", body}; body += esphttpdutils::htmlentities(appDesc->version); }
                    }

                    {
                        HtmlTag trTag{"tr", body};
                        { HtmlTag tdTag{"td", body}; body += "New secure_version"; }
                        { HtmlTag tdTag{"td", body}; body += std::to_string(appDesc->secure_version); }
                    }

                    {
                        HtmlTag trTag{"tr", body};
                        { HtmlTag tdTag{"td", body}; body += "New timestamp"; }
                        { HtmlTag tdTag{"td", body}; body += esphttpdutils::htmlentities(fmt::format("{} {}", appDesc->date, appDesc->time)); }
                    }

                    {
                        HtmlTag trTag{"tr", body};
                        { HtmlTag tdTag{"td", body}; body += "New idf_ver"; }
                        { HtmlTag tdTag{"td", body}; body += esphttpdutils::htmlentities(appDesc->idf_ver); }
                    }

                    {
                        HtmlTag trTag{"tr", body};
                        { HtmlTag tdTag{"td", body}; body += "New sha256"; }
                        { HtmlTag tdTag{"td", body}; body += esphttpdutils::htmlentities(espcpputils::toHexString({appDesc->app_elf_sha256, 8})); }
                    }
                }
            }
            else
            {
                HtmlTag pTag{"p", body};
                body += "Updater is sleeping (not constructed)";
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

                body += "url is only used temporarely and not persisted in flash";
            }
        }
    }

    CALL_AND_EXIT(esphttpdutils::webserver_resp_send, req, esphttpdutils::ResponseStatus::Ok, "text/html", body)
}

esp_err_t webserver_trigger_ota_handler(httpd_req_t *req)
{
    espcpputils::LockHelper helper{webserver_lock->handle, std::chrono::ceil<espcpputils::ticks>(5s).count()};
    if (!helper.locked())
    {
        constexpr const std::string_view msg = "could not lock webserver_lock";
        ESP_LOGE(TAG, "%.*s", msg.size(), msg.data());
        CALL_AND_EXIT(esphttpdutils::webserver_resp_send, req, esphttpdutils::ResponseStatus::BadRequest, "text/plain", msg);
    }

    std::string query;
    if (auto result = esphttpdutils::webserver_get_query(req))
        query = *result;
    else
    {
        ESP_LOGE(TAG, "%.*s", result.error().size(), result.error().data());
        CALL_AND_EXIT(esphttpdutils::webserver_resp_send, req, esphttpdutils::ResponseStatus::BadRequest, "text/plain", result.error());
    }

    std::string url;
    constexpr const std::string_view urlParamName{"url"};

    {
        char valueBufEncoded[256];
        if (const auto result = httpd_query_key_value(query.data(), urlParamName.data(), valueBufEncoded, 256); result != ESP_OK)
        {
            if (result == ESP_ERR_NOT_FOUND)
            {
                const auto msg = fmt::format("{} not set", urlParamName);
                ESP_LOGW(TAG, "%.*s", msg.size(), msg.data());
                CALL_AND_EXIT(esphttpdutils::webserver_resp_send, req, esphttpdutils::ResponseStatus::BadRequest, "text/plain", msg);
            }
            else
            {
                const auto msg = fmt::format("httpd_query_key_value() {} failed with {}", urlParamName, esp_err_to_name(result));
                ESP_LOGE(TAG, "%.*s", msg.size(), msg.data());
                CALL_AND_EXIT(esphttpdutils::webserver_resp_send, req, esphttpdutils::ResponseStatus::BadRequest, "text/plain", msg);
            }
        }

        char valueBuf[257];
        esphttpdutils::urldecode(valueBuf, valueBufEncoded);

        url = valueBuf;
    }

    if (const auto result = triggerOta(url); !result)
    {
        ESP_LOGE(TAG, "%.*s", result.error().size(), result.error().data());
        CALL_AND_EXIT(esphttpdutils::webserver_resp_send, req, esphttpdutils::ResponseStatus::BadRequest, "text/plain", result.error());
    }

    CALL_AND_EXIT_ON_ERROR(httpd_resp_set_hdr, req, "Location", "/ota")
    CALL_AND_EXIT(esphttpdutils::webserver_resp_send, req, esphttpdutils::ResponseStatus::TemporaryRedirect, "text/html", "Ok, continue at <a href=\"/ota\">/</a>")
}
}
#endif
