#pragma once

#ifdef FEATURE_ARDUINOOTA
#include <ArduinoOTA.h>
#endif

#include "screens.h"
#include "globals.h"
#include "displays/updatedisplay.h"

namespace {
#ifdef FEATURE_ARDUINOOTA
void initOta()
{
    ArduinoOTA
        .onStart([]() {
            std::to_string type;
            if (ArduinoOTA.getCommand() == U_FLASH)
                type = "sketch";
            else if (ArduinoOTA.getCommand() == U_SPIFFS) // U_SPIFFS
                type = "filesystem";
            else
                type = "unknown";

            switchScreenImpl<UpdateDisplay>("Updating " + type);
        })
        .onEnd([]() {
            ((UpdateDisplay*)currentDisplay.get())->m_finished = true;
            ((UpdateDisplay*)currentDisplay.get())->redraw();
        })
        .onProgress([](unsigned int progress, unsigned int total) {
            ((UpdateDisplay*)currentDisplay.get())->m_progress = progress;
            ((UpdateDisplay*)currentDisplay.get())->m_total = total;
            ((UpdateDisplay*)currentDisplay.get())->redraw();
        })
        .onError([](ota_error_t error) {
            ((UpdateDisplay*)currentDisplay.get())->m_error = error;
            ((UpdateDisplay*)currentDisplay.get())->m_errorValid = true;
            ((UpdateDisplay*)currentDisplay.get())->redraw();
        });

    ArduinoOTA.begin();
}

void handleOta()
{
    ArduinoOTA.handle();
}
#endif
}
