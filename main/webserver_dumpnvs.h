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
#include "globals.h"
#include "webserver_lock.h"
#include "settingsutils.h"

#ifdef FEATURE_WEBSERVER
namespace dump_nvs_handler {
esp_err_t webserver_dump_nvs_handler(httpd_req_t *req);
} // namespace

using esphttpdutils::HtmlTag;

namespace dump_nvs_handler {

template<typename T>
typename std::enable_if<
    !std::is_same<T, bool>::value &&
    !std::is_integral<T>::value &&
    !std::is_same<T, std::array<int8_t, 4>>::value
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
    body += fmt::format("<input type=\"checkbox\" readonly name=\"{}\" value=\"true\" {}/>"
                        "<input type=\"hidden\" readonly name=\"{}\" value=\"false\" />",
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
    body += fmt::format("<input type=\"number\" name=\"{}\" value=\"{}\" min=\"{}\" max=\"{}\" step=\"1\" required readonly/>",
                        esphttpdutils::htmlentities(key),
                        value,
                        std::numeric_limits<T>::min(),
                        std::numeric_limits<T>::max());
    return true;
}

template<typename T>
typename std::enable_if<
    std::is_same<T, std::array<int8_t, 4>>::value
, bool>::type
showInputForSetting(std::string_view key, T value, std::string &body)
{
    body += fmt::format("<input type=\"text\" name=\"{}\" value=\"{}{}{}{}\" pattern=\"[0-9]{{4}}\" required readonly/>",
                        esphttpdutils::htmlentities(key),
                        value[0],
                        value[1],
                        value[2],
                        value[3]);
    return true;
}

esp_err_t webserver_dump_nvs_handler(httpd_req_t *req)
{
    espcpputils::LockHelper helper{webserver_lock->handle, std::chrono::ceil<espcpputils::ticks>(5s).count()};
    if (!helper.locked())
    {
        constexpr const std::string_view msg = "could not lock webserver_lock";
        ESP_LOGE(TAG, "%.*s", msg.size(), msg.data());
        CALL_AND_EXIT(esphttpdutils::webserver_resp_send, req, esphttpdutils::ResponseStatus::BadRequest, "text/plain", msg);
    }

    std::string body;
    const auto profile = settingsPersister.currentlyOpenProfileIndex();
    const auto switchBackProfile = profile ? int(*profile) : 0;

    {
        HtmlTag htmlTag{"html", body};

        {
            HtmlTag headTag{"head", body};

            {
                HtmlTag titleTag{"title", body};
                body += "NVS dump";
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
                body += "NVS dump";
            }

            {
                HtmlTag pTag{"p", body};
                body += "<a href=\"/\">Display control</a> - "
#ifdef FEATURE_OTA
                        "<a href=\"/ota\">Update</a> - "
#endif
                        "<a href=\"/settings\">Settings</a> - "
                        "<a href=\"/stringSettings\">String Settings</a> - "
                        "<b>Dump NVS</b>";
            }

            HtmlTag divTag{"div", "class=\"form-table\"", body};
            // Common setting
            {
                HtmlTag h1Tag{"h1", body};
                body += "stringSettings";
            }
            stringSettings.executeForEveryCommonSetting([&](std::string_view key, const auto &value){
                HtmlTag divTag{"div", "class=\"form-table-row\"", body};

                {
                    HtmlTag divTag{"div", "class=\"form-table\"", body};
                    HtmlTag bTag{"b", body};
                    body += esphttpdutils::htmlentities(key);
                }

                {
                    HtmlTag divTag{"div", "class=\"form-table-cell\"", body};
                    body += fmt::format("<input type=\"text\" name=\"{}\" value=\"{}\" required readonly/>",
                                        esphttpdutils::htmlentities(key),
                                        esphttpdutils::htmlentities(value));
                }
            });

            {
                HtmlTag h1Tag{"h1", body};
                body += "settings";
            }
            settings.executeForEveryCommonSetting([&](std::string_view key, const auto &value){
                HtmlTag divTag{"div", "class=\"form-table-row\"", body};

                {
                    HtmlTag divTag{"div", "class=\"form-table\"", body};
                    HtmlTag bTag{"b", body};
                    body += esphttpdutils::htmlentities(key);
                }

                {
                    HtmlTag divTag{"div", "class=\"form-table-cell\"", body};
                    showInputForSetting(key, value, body);
                }
            });

            // ToDo: Do something that it does not crash (std::string probabbly gets to big)
            // After that, change "profile_num < 1" to "profile_num < 4", uncomment the "switchProfile(profile_num);" and reenable the url in webserver.h

            // Profile settings
            for (uint8_t profile_num = 0; profile_num < 1; profile_num++) {

#ifdef SIMPLIFIED_TRIGGER_TRIGGERONPRESET
                if (profile_num == SIMPLIFIED_TRIGGER_TRIGGERONPRESET) {
                    continue;
                }
#endif
                // switchProfile(profile_num);

                const auto cur_profile = settingsPersister.currentlyOpenProfileIndex();
                const auto cur_profile_int = profile ? int(*cur_profile) : 0;
                {
                    HtmlTag h1Tag{"h1", body};
                    body += fmt::format("stringSettings (Profile {})", cur_profile_int);
                }
                stringSettings.executeForEveryProfileSetting([&](const char *key, auto &value){
                    HtmlTag divTag{"div", "class=\"form-table-row\"", body};

                    {
                        HtmlTag divTag{"div", "class=\"form-table\"", body};
                        HtmlTag bTag{"b", body};
                        body += esphttpdutils::htmlentities(key);
                    }

                    {
                        HtmlTag divTag{"div", "class=\"form-table-cell\"", body};
                        body += fmt::format("<input type=\"text\" name=\"{}\" value=\"{}\" required readonly/>",
                                            esphttpdutils::htmlentities(key),
                                            esphttpdutils::htmlentities(value));
                    }
                });

                {
                    HtmlTag h1Tag{"h1", body};
                    body += fmt::format("settings (Profile {})", cur_profile_int);
                }
                settings.executeForEveryProfileSetting([&](const char *key, auto &value){
                    HtmlTag divTag{"div", "class=\"form-table-row\"", body};

                    {
                        HtmlTag divTag{"div", "class=\"form-table\"", body};
                        HtmlTag bTag{"b", body};
                        body += esphttpdutils::htmlentities(key);
                    }

                    {
                        HtmlTag divTag{"div", "class=\"form-table-cell\"", body};
                        showInputForSetting(key, value, body);
                    }
                });
            }
        }
    }

    switchProfile(switchBackProfile);

    CALL_AND_EXIT(esphttpdutils::webserver_resp_send, req, esphttpdutils::ResponseStatus::Ok, "text/html", body)
}
} // namespace

#endif

