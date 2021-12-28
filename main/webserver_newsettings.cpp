#include "webserver_newsettings.h"

// system includes
#include <limits>

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
#include <numberparsing.h>
#include <lockhelper.h>
#include <tickchrono.h>

// local includes
#include "newsettings.h"
#include "webserver_lock.h"

#ifdef FEATURE_WEBSERVER
using namespace std::chrono_literals;
using esphttpdutils::HtmlTag;

namespace {
constexpr const char * const TAG = "BOBBYWEB";

template<typename T>
typename std::enable_if<
    !std::is_same<T, bool>::value &&
    !std::is_integral<T>::value &&
    !std::is_same<T, std::string>::value &&
    !std::is_same<T, wifi_stack::ip_address_t>::value &&
    !std::is_same<T, wifi_stack::mac_t>::value
, bool>::type
showInputForSetting(std::string_view key, T value, std::string &body)
{
    HtmlTag spanTag{"span", "style=\"color: red;\"", body};
    body += "Unsupported config type";
    return false;
}

template<typename T>
typename std::enable_if<
    std::is_same<T, bool>::value
, bool>::type
showInputForSetting(std::string_view key, T value, std::string &body)
{
    body += fmt::format("<input type=\"checkbox\" name=\"{}\" value=\"true\" {}/>"
                        "<input type=\"hidden\" name=\"{}\" value=\"false\" />",
                        esphttpdutils::htmlentities(key),
                        value ? "checked " : "",
                        esphttpdutils::htmlentities(key));
    return true;
}

template<typename T>
typename std::enable_if<
    !std::is_same<T, bool>::value &&
    std::is_integral<T>::value
, bool>::type
showInputForSetting(std::string_view key, T value, std::string &body)
{
    body += fmt::format("<input type=\"number\" name=\"{}\" value=\"{}\" min=\"{}\" max=\"{}\" step=\"1\" />",
                        esphttpdutils::htmlentities(key),
                        value,
                        std::numeric_limits<T>::min(),
                        std::numeric_limits<T>::max());
    return true;
}

template<typename T>
typename std::enable_if<
    std::is_same<T, std::string>::value
, bool>::type
showInputForSetting(std::string_view key, T value, std::string &body)
{
    body += fmt::format("<input type=\"text\" name=\"{}\" value=\"{}\" />",
                        esphttpdutils::htmlentities(key),
                        esphttpdutils::htmlentities(value));
    return true;
}

template<typename T>
typename std::enable_if<
    std::is_same<T, wifi_stack::ip_address_t>::value
, bool>::type
showInputForSetting(std::string_view key, T value, std::string &body)
{
    body += fmt::format("<input type=\"text\" name=\"{}\" value=\"{}\" pattern=\"[0-9]+\\.[0-9]+\\.[0-9]+\\.[0-9]+\" />",
                        esphttpdutils::htmlentities(key),
                        esphttpdutils::htmlentities(wifi_stack::toString(value)));
    return true;
}

template<typename T>
typename std::enable_if<
    std::is_same<T, wifi_stack::mac_t>::value
, bool>::type
showInputForSetting(std::string_view key, T value, std::string &body)
{
    body += fmt::format("<input type=\"text\" name=\"{}\" value=\"{}\" pattern=\"[0-9a-fA-F]{2}(?:\\:[0-9a-fA-F]{2}){5}\" />",
                        esphttpdutils::htmlentities(key),
                        esphttpdutils::htmlentities(wifi_stack::toString(value)));
    return true;
}
} // namespace

esp_err_t webserver_newSettings_handler(httpd_req_t *req)
{
#ifndef FEATURE_IS_MIR_EGAL_OB_DER_WEBSERVER_KORREKT_ARBEITET
    espcpputils::LockHelper helper{webserver_lock->handle, std::chrono::ceil<espcpputils::ticks>(5s).count()};
    if (!helper.locked())
    {
        constexpr const std::string_view msg = "could not lock webserver_lock";
        ESP_LOGE(TAG, "%.*s", msg.size(), msg.data());
        CALL_AND_EXIT(esphttpdutils::webserver_resp_send, req, esphttpdutils::ResponseStatus::BadRequest, "text/plain", msg);
    }
#endif

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

            HtmlTag styleTag{"style", "type=\"text/css\"", body};
            body +=
                ".form-table {"
                "display: table;"
                "border-collapse: separate;"
                "border-spacing: 10px 0;"
                "}"

                ".form-table .form-table-row {"
                "display: table-row;"
                "}"

                ".form-table .form-table-row .form-table-cell {"
                "display: table-cell;"
                "}";
        }

        {
            HtmlTag bodyTag{"body", body};

            {
                HtmlTag h1Tag{"h1", body};
                body += "Settings";
            }

            {
                HtmlTag pTag{"p", body};
                body += "<a href=\"/\">Display control</a> - "
#ifdef FEATURE_OTA
                        "<a href=\"/ota\">Update</a> - "
#endif
                        "<a href=\"/settings\">Settings</a> - "
                        "<a href=\"/stringSettings\">String Settings</a> - "
                        "<b>New Settings</b> - "
                        "<a href=\"/dumpnvs\">Dump NVS</a>";
            }

            HtmlTag divTag{"div", "class=\"form-table\"", body};

            configs.callForEveryConfig([&](const auto &config){
                if (body.size() > 2048)
                {
                    if (const auto result = httpd_resp_send_chunk(req, body.data(), body.size()); result != ESP_OK)
                    {
                        ESP_LOGE(TAG, "httpd_resp_send_chunk() failed with %s", esp_err_to_name(result));
                        //return result;
                    }
                    body.clear();
                }

                const std::string_view nvsName{config.nvsName()};

                HtmlTag formTag{"form", "class=\"form-table-row\" action=\"/saveNewSettings\" method=\"GET\"", body};

                {
                    HtmlTag divTag{"div", "class=\"form-table\"", body};
                    HtmlTag bTag{"b", body};
                    body += esphttpdutils::htmlentities(nvsName);
                }

                {
                    HtmlTag divTag{"div", "class=\"form-table-cell\"", body};
                    showInputForSetting(nvsName, config.value, body);
                }

                {
                    HtmlTag divTag{"div", "class=\"form-table-cell\"", body};
                    HtmlTag buttonTag{"button", "type=\"submit\"", body};
                    body += "Save";
                }
            });
        }
    }

    CALL_AND_EXIT_ON_ERROR(httpd_resp_send_chunk, req, body.data(), body.size());
    body.clear();
    CALL_AND_EXIT(httpd_resp_send_chunk, req, nullptr, 0);
    //CALL_AND_EXIT(esphttpdutils::webserver_resp_send, req, esphttpdutils::ResponseStatus::Ok, "text/html", body)
}

namespace {
template<typename T>
typename std::enable_if<
    !std::is_same<T, bool>::value &&
    !std::is_integral<T>::value &&
    !std::is_same<T, std::string>::value &&
    !std::is_same<T, wifi_stack::ip_address_t>::value &&
    !std::is_same<T, wifi_stack::mac_t>::value
, bool>::type
saveSetting(ConfigWrapper<T> &config, std::string_view newValue, std::string &body)
{
    body += "Unsupported config type";
    return false;
}

template<typename T>
typename std::enable_if<
    std::is_same<T, bool>::value
, bool>::type
saveSetting(ConfigWrapper<T> &config, std::string_view newValue, std::string &body)
{
    if (newValue == "true")
    {
        if (const auto result = configs.write_config(config, true); result)
        {
            body += "applied";
            return true;
        }
        else
        {
            body += result.error();
            return false;
        }
    }
    else if (newValue == "false")
    {
        if (const auto result = configs.write_config(config, false); result)
        {
            body += "applied";
            return true;
        }
        else
        {
            body += result.error();
            return false;
        }
    }
    else
    {
        body += fmt::format("only true and false allowed, not {}", newValue);
        return false;
    }
}

template<typename T>
typename std::enable_if<
    !std::is_same<T, bool>::value &&
    std::is_integral<T>::value
, bool>::type
saveSetting(ConfigWrapper<T> &config, std::string_view newValue, std::string &body)
{
    if (auto parsed = cpputils::fromString<T>(newValue))
    {
        if (const auto result = configs.write_config(config, *parsed); result)
        {
            body += "applied";
            return true;
        }
        else
        {
            body += result.error();
            return false;
        }
    }
    else
    {
        body += fmt::format("could not parse {}", newValue);
        return false;
    }
}

template<typename T>
typename std::enable_if<
    std::is_same<T, std::string>::value
, bool>::type
saveSetting(ConfigWrapper<T> &config, std::string_view newValue, std::string &body)
{
    if (const auto result = configs.write_config(config, std::string{newValue}); result)
    {
        body += "applied";
        return true;
    }
    else
    {
        body += result.error();
        return false;
    }
}

template<typename T>
typename std::enable_if<
    std::is_same<T, wifi_stack::ip_address_t>::value
, bool>::type
saveSetting(ConfigWrapper<T> &config, std::string_view newValue, std::string &body)
{
    if (const auto parsed = wifi_stack::fromString<wifi_stack::ip_address_t>(newValue); parsed)
    {
        if (const auto result = configs.write_config(config, *parsed); result)
        {
            body += "applied";
            return true;
        }
        else
        {
            body += result.error();
            return false;
        }
    }
    else
    {
        body += parsed.error();
        return false;
    }
}

template<typename T>
typename std::enable_if<
    std::is_same<T, wifi_stack::mac_t>::value
, bool>::type
saveSetting(ConfigWrapper<T> &config, std::string_view newValue, std::string &body)
{
    if (const auto parsed = wifi_stack::fromString<wifi_stack::mac_t>(newValue); parsed)
    {
        if (const auto result = configs.write_config(config, *parsed); result)
        {
            body += "applied";
            return true;
        }
        else
        {
            body += result.error();
            return false;
        }
    }
    else
    {
        body += parsed.error();
        return false;
    }
}
} // namespace

esp_err_t webserver_saveNewSettings_handler(httpd_req_t *req)
{
#ifndef FEATURE_IS_MIR_EGAL_OB_DER_WEBSERVER_KORREKT_ARBEITET
    espcpputils::LockHelper helper{webserver_lock->handle, std::chrono::ceil<espcpputils::ticks>(5s).count()};
    if (!helper.locked())
    {
        constexpr const std::string_view msg = "could not lock webserver_lock";
        ESP_LOGE(TAG, "%.*s", msg.size(), msg.data());
        CALL_AND_EXIT(esphttpdutils::webserver_resp_send, req, esphttpdutils::ResponseStatus::BadRequest, "text/plain", msg);
    }
#endif

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

    configs.callForEveryConfig([&](auto &config){
        const std::string_view nvsName{config.nvsName()};

        char valueBufEncoded[256];
        if (const auto result = httpd_query_key_value(query.data(), nvsName.data(), valueBufEncoded, 256); result != ESP_OK)
        {
            if (result != ESP_ERR_NOT_FOUND)
            {
                const auto msg = fmt::format("{}: httpd_query_key_value() failed with {}", nvsName, esp_err_to_name(result));
                ESP_LOGE(TAG, "%.*s", msg.size(), msg.data());
                body += msg;
                body += '\n';
                success = false;
            }
            return;
        }

        char valueBuf[257];
        esphttpdutils::urldecode(valueBuf, valueBufEncoded);

        body += nvsName;
        if (!saveSetting(config, valueBuf, body))
            success = false;
        body += '\n';
    });

    if (body.empty())
        CALL_AND_EXIT(esphttpdutils::webserver_resp_send, req, esphttpdutils::ResponseStatus::Ok, "text/plain", "nothing changed?!")

    if (success)
    {
        CALL_AND_EXIT_ON_ERROR(httpd_resp_set_hdr, req, "Location", "/newSettings")
        body += "\nOk, continue at /newSettings";
    }

    CALL_AND_EXIT(esphttpdutils::webserver_resp_send,
                  req,
                  success ? esphttpdutils::ResponseStatus::TemporaryRedirect : esphttpdutils::ResponseStatus::BadRequest,
                  "text/plain",
                  body)
}
#endif
