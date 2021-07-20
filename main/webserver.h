#pragma once

// system includes
#include <atomic>

// esp-idf includes
#ifdef FEATURE_WEBSERVER
#include <esp_http_server.h>
#endif
#include <esp_log.h>

// local includes
#include "screens.h"
#include "textinterface.h"
#include "menudisplay.h"
#include "changevaluedisplay.h"
#include "displays/updatedisplay.h"
//#include "esputils.h"
#include "buttons.h"
#include "espcppmacros.h"

namespace {
#ifdef FEATURE_WEBSERVER
httpd_handle_t httpdHandle;

std::atomic<bool> shouldReboot;

class HtmlTag {
public:
    HtmlTag(const char *tagName, std::string &body) :
        m_tagName{tagName},
        m_body{body}
    {
        m_body += '<';
        m_body += m_tagName;
        m_body += '>';
    }

    ~HtmlTag()
    {
        m_body += "</";
        m_body += m_tagName;
        m_body += '>';
    }

private:
    const char * const m_tagName;
    std::string &m_body;
};

esp_err_t webserver_root_handler(httpd_req_t *req);
esp_err_t webserver_up_handler(httpd_req_t *req);
esp_err_t webserver_down_handler(httpd_req_t *req);
esp_err_t webserver_confirm_handler(httpd_req_t *req);
esp_err_t webserver_back_handler(httpd_req_t *req);
esp_err_t webserver_triggerItem_handler(httpd_req_t *req);
esp_err_t webserver_setValue_handler(httpd_req_t *req);
esp_err_t webserver_reboot_handler(httpd_req_t *req);

void initWebserver()
{
    shouldReboot = false;

    {
        httpd_config_t httpConfig HTTPD_DEFAULT_CONFIG();
        httpConfig.core_id = 1;

        const auto result = httpd_start(&httpdHandle, &httpConfig);
        ESP_LOG_LEVEL_LOCAL((result == ESP_OK ? ESP_LOG_INFO : ESP_LOG_ERROR), TAG, "httpd_start(): %s", esp_err_to_name(result));
        if (result != ESP_OK)
            return;
    }

    for (const httpd_uri_t &uri : {
         httpd_uri_t { .uri = "/",            .method = HTTP_GET, .handler = webserver_root_handler,        .user_ctx = NULL },
         httpd_uri_t { .uri = "/up",          .method = HTTP_GET, .handler = webserver_up_handler,          .user_ctx = NULL },
         httpd_uri_t { .uri = "/down",        .method = HTTP_GET, .handler = webserver_down_handler,        .user_ctx = NULL },
         httpd_uri_t { .uri = "/confirm",     .method = HTTP_GET, .handler = webserver_confirm_handler,     .user_ctx = NULL },
         httpd_uri_t { .uri = "/back",        .method = HTTP_GET, .handler = webserver_back_handler,        .user_ctx = NULL },
         httpd_uri_t { .uri = "/triggerItem", .method = HTTP_GET, .handler = webserver_triggerItem_handler, .user_ctx = NULL },
         httpd_uri_t { .uri = "/setValue",    .method = HTTP_GET, .handler = webserver_setValue_handler,    .user_ctx = NULL },
         httpd_uri_t { .uri = "/reboot",      .method = HTTP_GET, .handler = webserver_reboot_handler,      .user_ctx = NULL }
    })
    {
        const auto result = httpd_register_uri_handler(httpdHandle, &uri);
        ESP_LOG_LEVEL_LOCAL((result == ESP_OK ? ESP_LOG_INFO : ESP_LOG_ERROR), TAG, "httpd_register_uri_handler() for %s: %s", uri.uri, esp_err_to_name(result));
        //if (result != ESP_OK)
        //    return result;
    }

#ifdef FEATURE_WEBOTA
    webServer.on("/update", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200, "text/html",
                      "<form method=\"POST\" action=\"/updateCode\" enctype=\"multipart/form-data\">"
                      "<input type=\"file\" name=\"update\">"
                      "<input type=\"submit\" value=\"Update Code\">"
                      "</form>"
                      "<form method=\"POST\" action=\"/updateData\" enctype=\"multipart/form-data\">"
                      "<input type=\"file\" name=\"update\">"
                      "<input type=\"submit\" value=\"Update Data\">"
                      "</form>");
    });

    const auto handleUpdate = [](AsyncWebServerRequest *request){
        shouldReboot = !Update.hasError();

        AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", shouldReboot ? "OK" : "FAIL");
        response->addHeader("Connection", "close");
        request->send(response);
    };

    const auto createHandleUpdtateUpload = [](size_t size, int command){
        return [size, command](AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final){
            //ESP_UNUSED(request)

            //Serial.printf("callback %u %u\r\n", index, len);

            if (!index)
            {
                //Serial.printf("Update Start: %s\r\n", filename.c_str());
                //Update.runAsync(true);
                if (!Update.begin(size, command))
                    Update.printError(Serial);

                std::string type;
                if (ArduinoOTA.getCommand() == U_FLASH)
                    type = "sketch";
                else if (ArduinoOTA.getCommand() == U_SPIFFS) // U_SPIFFS
                    type = "filesystem";
                else
                    type = "unknown";

                switchScreenImpl<UpdateDisplay>("Updating " + type);
            }

            if (!Update.hasError())
            {
                if (Update.write(data, len) == len)
                {
                    ((UpdateDisplay*)currentDisplay.get())->m_progress = index;
                    ((UpdateDisplay*)currentDisplay.get())->m_total = size;
                    ((UpdateDisplay*)currentDisplay.get())->redraw();
                }
                else
                {
                    Update.printError(Serial);

                    ((UpdateDisplay*)currentDisplay.get())->m_error = {};
                    ((UpdateDisplay*)currentDisplay.get())->m_errorValid = true;
                    ((UpdateDisplay*)currentDisplay.get())->redraw();
                }
            }
            else
            {
                ((UpdateDisplay*)currentDisplay.get())->m_error = {};
                ((UpdateDisplay*)currentDisplay.get())->m_errorValid = true;
                ((UpdateDisplay*)currentDisplay.get())->redraw();
            }

            if (final)
            {
                if (Update.end(true))
                {
                    //Serial.printf("Update Success: %uB\r\n", index + len);

                    ((UpdateDisplay*)currentDisplay.get())->m_finished = true;
                    ((UpdateDisplay*)currentDisplay.get())->redraw();
                }
                else
                {
                    Update.printError(Serial);

                    ((UpdateDisplay*)currentDisplay.get())->m_error = {};
                    ((UpdateDisplay*)currentDisplay.get())->m_errorValid = true;
                    ((UpdateDisplay*)currentDisplay.get())->redraw();
                }
            }
        };
    };

    webServer.on("/updateCode", HTTP_POST, handleUpdate, createHandleUpdtateUpload((ESP.getFreeSketchSpace() - 0x1000) & 0xFFFFF000, U_FLASH));
    webServer.on("/updateData", HTTP_POST, handleUpdate, createHandleUpdtateUpload(UPDATE_SIZE_UNKNOWN, U_SPIFFS));
#endif
}

void handleWebserver()
{
    if (shouldReboot)
    {
        shouldReboot = false;
        esp_restart();
    }
}

esp_err_t webserver_root_handler(httpd_req_t *req)
{
    std::string body;

    {
        HtmlTag htmlTag{"html", body};

        {
            HtmlTag headTag{"head", body};

            {
                HtmlTag titleTag{"title", body};
                body += ("Bobbycar remote");
            }

            body += ("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1, shrink-to-fit=no\" />");
        }

        {
            HtmlTag bodyTag{"body", body};

            {
                HtmlTag h1Tag{"h1", body};
                body += ("Bobbycar remote");
            }

            {
                HtmlTag pTag{"p", body};
                body += ("<a href=\"/up\">Up</a> "
                                "<a href=\"/down\">Down</a> "
                                "<a href=\"/confirm\">Confirm</a> "
                                "<a href=\"/back\">Back</a>");
            }

            if (auto constCurrentDisplay = static_cast<const Display *>(currentDisplay.get()))
            {
                if (const auto *textInterface = constCurrentDisplay->asTextInterface())
                {
                    HtmlTag h2Tag{"h2", body};
                    body += (textInterface->text().c_str());
                }

                if (const auto *menuDisplay = constCurrentDisplay->asMenuDisplay())
                {
                    HtmlTag ulTag{"ul", body};

                    int i{0};
                    menuDisplay->runForEveryMenuItem([&,selectedIndex=menuDisplay->selectedIndex()](const MenuItem &menuItem){
                        body += ("<li");

                        if (i == selectedIndex)
                            body += (" style=\"border: 1px solid black;\"");

                        body += ("><a href=\"/triggerItem?index=");
                        body += (i);
                        body += ("\">");
                        body += (menuItem.text().c_str());
                        body += ("</a></li>");

                        i++;
                    });
                }
                else if (const auto *changeValueDisplay = constCurrentDisplay->asChangeValueDisplayInterface())
                {
                    body += ("<form action=\"/setValue\" method=\"GET\">");
                    body += (("<input type=\"number\" name=\"value\" value=\"" + std::to_string(changeValueDisplay->shownValue()) + "\" />").c_str());
                    body += ("<button type=\"submit\">Update</button>");
                    body += ("</form>");
                }
                else
                {
                    body += ("No web control implemented for current display.");
                }
            }
            else
            {
                body += ("Currently no screen instantiated.");
            }
        }
    }

    CALL_AND_EXIT_ON_ERROR(httpd_resp_set_type, req, "text/html")
    CALL_AND_EXIT_ON_ERROR(httpd_resp_send, req, body.data(), body.size())

    return ESP_OK;
}

esp_err_t webserver_up_handler(httpd_req_t *req)
{
#ifdef OLD_CODE
    InputDispatcher::rotate(-1);

    AsyncWebServerResponse *response = request->beginResponse(302, "text/plain", "ok");
    response->addHeader("Location", "/");
    request->send(response);
#else
    return ESP_OK;
#endif
}

esp_err_t webserver_down_handler(httpd_req_t *req)
{
#ifdef OLD_CODE
    InputDispatcher::rotate(1);

    AsyncWebServerResponse *response = request->beginResponse(302, "text/plain", "ok");
    response->addHeader("Location", "/");
    request->send(response);
#else
    return ESP_OK;
#endif
}

esp_err_t webserver_confirm_handler(httpd_req_t *req)
{
#ifdef OLD_CODE
    InputDispatcher::confirmButton(true);
    InputDispatcher::confirmButton(false);

    AsyncWebServerResponse *response = request->beginResponse(302, "text/plain", "ok");
    response->addHeader("Location", "/");
    request->send(response);
#else
    return ESP_OK;
#endif
}

esp_err_t webserver_back_handler(httpd_req_t *req)
{
#ifdef OLD_CODE
    InputDispatcher::backButton(true);
    InputDispatcher::backButton(false);

    AsyncWebServerResponse *response = request->beginResponse(302, "text/plain", "ok");
    response->addHeader("Location", "/");
    request->send(response);
#else
    return ESP_OK;
#endif
}

esp_err_t webserver_triggerItem_handler(httpd_req_t *req)
{
#ifdef OLD_CODE
    if (!request->hasArg("index"))
    {
        request->send(400, "text/plain", "index parameter missing");
        return;
    }

    if (!currentDisplay)
    {
        request->send(400, "text/plain", "currentDisplay is null");
        return;
    }

    auto *menuDisplay = currentDisplay->asMenuDisplay();
    if (!menuDisplay)
    {
        request->send(400, "text/plain", "currentDisplay is not a menu display");
        return;
    }

    const auto indexStr = request->arg("index");

    char *ptr;
    const auto index = std::strtol(std::begin(indexStr), &ptr, 10);

    if (ptr != std::end(indexStr))
    {
        request->send(400, "text/plain", "index could not be parsed");
        return;
    }

    if (index < 0 || index >= menuDisplay->menuItemCount())
    {
        request->send(400, "text/plain", "index out of range");
        return;
    }

    menuDisplay->getMenuItem(index).triggered();

    AsyncWebServerResponse *response = request->beginResponse(302, "text/plain", "ok");
    response->addHeader("Location", "/");
    request->send(response);
#else
    return ESP_OK;
#endif
}

esp_err_t webserver_setValue_handler(httpd_req_t *req)
{
#ifdef OLD_CODE
    if (!request->hasArg("value"))
    {
        request->send(400, "text/plain", "value parameter missing");
        return;
    }

    if (!currentDisplay)
    {
        request->send(400, "text/plain", "currentDisplay is null");
        return;
    }

    auto *changeValueDisplay = currentDisplay->asChangeValueDisplayInterface();
    if (!changeValueDisplay)
    {
        request->send(400, "text/plain", "currentDisplay is not a change value display");
        return;
    }

    const auto valueStr = request->arg("value");

    char *ptr;
    const auto value = std::strtol(std::begin(valueStr), &ptr, 10);

    if (ptr != std::end(valueStr))
    {
        request->send(400, "text/plain", "value could not be parsed");
        return;
    }

    changeValueDisplay->setShownValue(value);

    AsyncWebServerResponse *response = request->beginResponse(302, "text/plain", "ok");
    response->addHeader("Location", "/");
    request->send(response);
#else
    return ESP_OK;
#endif
}

esp_err_t webserver_reboot_handler(httpd_req_t *req)
{
    std::string_view body{"REBOOT called..."};
    CALL_AND_EXIT_ON_ERROR(httpd_resp_set_type, req, "text/html")
    CALL_AND_EXIT_ON_ERROR(httpd_resp_send, req, body.data(), body.size())

    shouldReboot = true;

    return ESP_OK;
}

#endif
}
