#pragma once

// 3rdparty lib includes
#include <ESPAsyncWebServer.h>

// local includes
#include "screens.h"
#include "textinterface.h"
#include "menudisplay.h"
#include "changevaluedisplay.h"

namespace {
#ifdef FEATURE_WEBSERVER
AsyncWebServer webServer{80};

class HtmlTag {
public:
    HtmlTag(const char *tagName, AsyncResponseStream *response) :
        m_tagName{tagName},
        m_response{response}
    {
        m_response->printf("<%s>", m_tagName);
    }

    ~HtmlTag()
    {
        m_response->printf("</%s>", m_tagName);
    }

private:
    const char * const m_tagName;
    AsyncResponseStream * const m_response;
};

void initWebserver()
{
    DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");

    webServer.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        AsyncResponseStream *response = request->beginResponseStream("text/html");

        {
            HtmlTag htmlTag{"html", response};

            {
                HtmlTag headTag{"head", response};

                {
                    HtmlTag titleTag{"title", response};
                    response->print("Bobbycar remote");
                }

                response->print("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1, shrink-to-fit=no\" />");
            }

            {
                HtmlTag bodyTag{"body", response};

                {
                    HtmlTag h1Tag{"h1", response};
                    response->print("Bobbycar remote");
                }

                {
                    HtmlTag pTag{"p", response};
                    response->print("<a href=\"/up\">Up</a> "
                                    "<a href=\"/down\">Down</a> "
                                    "<a href=\"/confirm\">Confirm</a> "
                                    "<a href=\"/back\">Back</a>");
                }

                if (auto constCurrentDisplay = static_cast<const Display *>(currentDisplay.get()))
                {
                    if (const auto *textInterface = constCurrentDisplay->asTextInterface())
                    {
                        HtmlTag h2Tag{"h2", response};
                        response->print(textInterface->text());
                    }

                    if (const auto *menuDisplay = constCurrentDisplay->asMenuDisplay())
                    {
                        HtmlTag ulTag{"ul", response};

                        int i{0};
                        menuDisplay->runForEveryMenuItem([&,selectedIndex=menuDisplay->selectedIndex()](const MenuItem &menuItem){
                            response->print("<li");

                            if (i == selectedIndex)
                                response->print(" style=\"border: 1px solid black;\"");

                            response->print("><a href=\"/triggerItem?index=");
                            response->print(i);
                            response->print("\">");
                            response->print(menuItem.text());
                            response->print("</a></li>");

                            i++;
                        });
                    }
                    else if (const auto *changeValueDisplay = constCurrentDisplay->asChangeValueDisplayInterface())
                    {
                        response->print("<form action=\"/setValue\" method=\"GET\">");
                        response->print("<input type=\"number\" name=\"value\" value=\"" + String{changeValueDisplay->shownValue()} + "\" />");
                        response->print("<button type=\"submit\">Update</button>");
                        response->print("</form>");
                    }
                    else
                    {
                        response->print("No web control implemented for current display.");
                    }
                }
                else
                {
                    response->print("Currently no screen instantiated.");
                }
            }
        }

        request->send(response);
    });

    webServer.on("/up", HTTP_GET, [](AsyncWebServerRequest *request){
        InputDispatcher::rotate(-1);

        AsyncWebServerResponse *response = request->beginResponse(302, "text/plain", "ok");
        response->addHeader("Location", "/");
        request->send(response);
    });

    webServer.on("/down", HTTP_GET, [](AsyncWebServerRequest *request){
        InputDispatcher::rotate(1);

        AsyncWebServerResponse *response = request->beginResponse(302, "text/plain", "ok");
        response->addHeader("Location", "/");
        request->send(response);
    });

    webServer.on("/confirm", HTTP_GET, [](AsyncWebServerRequest *request){
        InputDispatcher::confirmButton(true);
        InputDispatcher::confirmButton(false);

        AsyncWebServerResponse *response = request->beginResponse(302, "text/plain", "ok");
        response->addHeader("Location", "/");
        request->send(response);
    });

    webServer.on("/back", HTTP_GET, [](AsyncWebServerRequest *request){
        InputDispatcher::backButton(true);
        InputDispatcher::backButton(false);

        AsyncWebServerResponse *response = request->beginResponse(302, "text/plain", "ok");
        response->addHeader("Location", "/");
        request->send(response);
    });

    webServer.on("/triggerItem", HTTP_GET, [](AsyncWebServerRequest *request){
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

        if (index < 0 || index >= menuDisplay->size())
        {
            request->send(400, "text/plain", "index out of range");
            return;
        }

        menuDisplay->getMenuItem(index).triggered();

        AsyncWebServerResponse *response = request->beginResponse(302, "text/plain", "ok");
        response->addHeader("Location", "/");
        request->send(response);
    });

    webServer.on("/setValue", HTTP_GET, [](AsyncWebServerRequest *request){
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
    });

    webServer.begin();
}

void handleWebserver()
{
}
#endif
}
