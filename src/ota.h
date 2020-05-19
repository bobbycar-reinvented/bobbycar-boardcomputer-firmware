#pragma once

#include <ArduinoOTA.h>

#include "screens.h"
#include "displays/updatedisplay.h"

namespace {
void initOta()
{
    ArduinoOTA
        .onStart([]() {
            String type;
            if (ArduinoOTA.getCommand() == U_FLASH)
                type = "sketch";
            else if (ArduinoOTA.getCommand() == U_SPIFFS) // U_SPIFFS
                type = "filesystem";
            else
                type = "unknown";

            switchScreenImpl<UpdateDisplay>("Updating " + type);
        })
        .onEnd([]() {
            getRefByType<UpdateDisplay>().m_finished = true;
            getRefByType<UpdateDisplay>().redraw();
        })
        .onProgress([](unsigned int progress, unsigned int total) {
            getRefByType<UpdateDisplay>().m_progress = progress;
            getRefByType<UpdateDisplay>().m_total = total;
            getRefByType<UpdateDisplay>().redraw();
        })
        .onError([](ota_error_t error) {
            getRefByType<UpdateDisplay>().m_error = error;
            getRefByType<UpdateDisplay>().m_errorValid = true;
            getRefByType<UpdateDisplay>().redraw();
        });

    ArduinoOTA.begin();
}

void handleOta()
{
    ArduinoOTA.handle();
}
}
