#pragma once

#include <WebServer.h>

#include "screens.h"

namespace {
#ifdef FEATURE_WEBSERVER
WebServer webServer{80};

class HtmlTag {
public:
    HtmlTag(const String &tagName, String &content) :
        m_tagName{tagName},
        m_content{content}
    {
        content += "<" + tagName + ">";
    }

    ~HtmlTag()
    {
        m_content += "</" + m_tagName + ">";
    }

private:
    const String m_tagName;
    String &m_content;
};

void initWebserver()
{
    webServer.on("/", HTTP_GET, [](){
        webServer.sendHeader("Connection", "close");

        String content;

        {
            HtmlTag htmlTag{"html", content};

            {
                HtmlTag headTag{"head", content};

                {
                    HtmlTag titleTag{"title", content};
                    content += "Bobbycar remote";
                }

                content += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1, shrink-to-fit=no\" />";
            }

            {
                HtmlTag bodyTag{"body", content};

                {
                    HtmlTag h1Tag{"h1", content};
                    content += "Bobbycar remote";
                }

                {
                    HtmlTag pTag{"p", content};

                    content += "<a href=\"/up\">Up</a> <a href=\"/down\">Down</a> <a href=\"/confirm\">Confirm</a> <a href=\"/back\">Back</a>";
                }

                if (auto constCurrentDisplay = static_cast<const Display *>(currentDisplay))
                {
                    if (const auto *textInterface = constCurrentDisplay->asTextInterface())
                    {
                        HtmlTag h2Tag{"h2", content};
                        content += textInterface->text();
                    }

                    if (const auto *menuDisplay = constCurrentDisplay->asMenuDisplay())
                    {
                        HtmlTag ulTag{"ul", content};

                        int i{0};
                        menuDisplay->runForEveryMenuItem([&,selectedIndex=menuDisplay->selectedIndex()](const MenuItem &menuItem){
                            content += "<li";

                            if (i == selectedIndex)
                                content += " style=\"border: 1px solid black;\"";

                            content += "><a href=\"/triggerItem?index=";
                            content += i;
                            content += "\">";
                            content += menuItem.text();
                            content += "</a></li>";

                            i++;
                        });
                    }
                    else if (const auto *changeValueDisplay = constCurrentDisplay->asChangeValueDisplayInterface())
                    {
                        content += "<form action=\"/setValue\" method=\"GET\">";
                        content += "<input type=\"number\" name=\"value\" value=\"" + String{changeValueDisplay->shownValue()} + "\" />";
                        content += "<button type=\"submit\">Update</button>";
                        content += "</form>";
                    }
                    else
                    {
                        content += "No web control implemented for current display.";
                    }
                }
                else
                {
                    content += "Currently no screen instantiated.";
                }
            }
        }

        webServer.send(200, "text/html", content);
    });

    webServer.on("/up", HTTP_GET, [](){
        InputDispatcher::rotate(-1);

        webServer.sendHeader("Connection", "close");
        webServer.sendHeader("Location", "/");
        webServer.send(302, "text/html", "ok");
    });

    webServer.on("/down", HTTP_GET, [](){
        InputDispatcher::rotate(1);

        webServer.sendHeader("Connection", "close");
        webServer.sendHeader("Location", "/");
        webServer.send(302, "text/html", "ok");
    });

    webServer.on("/confirm", HTTP_GET, [](){
        InputDispatcher::confirmButton(true);
        InputDispatcher::confirmButton(false);

        webServer.sendHeader("Connection", "close");
        webServer.sendHeader("Location", "/");
        webServer.send(302, "text/html", "ok");
    });

    webServer.on("/back", HTTP_GET, [](){
        InputDispatcher::backButton(true);
        InputDispatcher::backButton(false);

        webServer.sendHeader("Connection", "close");
        webServer.sendHeader("Location", "/");
        webServer.send(302, "text/html", "ok");
    });

    webServer.on("/triggerItem", HTTP_GET, [](){
        if (!webServer.hasArg("index"))
        {
            webServer.send(400, "text/plain", "index parameter missing");
            return;
        }

        if (!currentDisplay)
        {
            webServer.send(400, "text/plain", "currentDisplay is null");
            return;
        }

        auto *menuDisplay = currentDisplay->asMenuDisplay();
        if (!menuDisplay)
        {
            webServer.send(400, "text/plain", "currentDisplay is not a menu display");
            return;
        }

        const auto indexStr = webServer.arg("index");

        char *ptr;
        const auto index = std::strtol(std::begin(indexStr), &ptr, 10);

        if (ptr != std::end(indexStr))
        {
            webServer.send(400, "text/plain", "index could not be parsed");
            return;
        }

        if (index < 0 || index >= menuDisplay->size())
        {
            webServer.send(400, "text/plain", "index out of range");
            return;
        }

        menuDisplay->getMenuItem(index).triggered();

        webServer.sendHeader("Connection", "close");
        webServer.sendHeader("Location", "/");
        webServer.send(302, "text/html", "ok");
    });

    webServer.on("/setValue", HTTP_GET, [](){
        if (!webServer.hasArg("value"))
        {
            webServer.send(400, "text/plain", "value parameter missing");
            return;
        }

        if (!currentDisplay)
        {
            webServer.send(400, "text/plain", "currentDisplay is null");
            return;
        }

        auto *changeValueDisplay = currentDisplay->asChangeValueDisplayInterface();
        if (!changeValueDisplay)
        {
            webServer.send(400, "text/plain", "currentDisplay is not a change value display");
            return;
        }

        const auto valueStr = webServer.arg("value");

        char *ptr;
        const auto value = std::strtol(std::begin(valueStr), &ptr, 10);

        if (ptr != std::end(valueStr))
        {
            webServer.send(400, "text/plain", "value could not be parsed");
            return;
        }

        changeValueDisplay->setShownValue(value);

        webServer.sendHeader("Connection", "close");
        webServer.sendHeader("Location", "/");
        webServer.send(302, "text/html", "ok");
    });

    webServer.begin();
}

void handleWebserver()
{
    webServer.handleClient();
}
#endif
}
