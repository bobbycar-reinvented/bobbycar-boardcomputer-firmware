#include "screens.h"

// 3rdparty lib includes
#include <tftinstance.h>
#include <screenmanager.h>

// local includes
#include "esptexthelpers.h"
#include "globals.h"
#include "utils.h"
#include "icons/logo.h"

using namespace espgui;

Label bootLabel{32, 250};

void initScreen()
{
    tft.init();
    tft.fillScreen(TFT_WHITE);
    tft.setTextColor(TFT_BLACK, TFT_WHITE);
    tft.setTextFont(4);
    espgui::tft.setSwapBytes(true);
    tft.pushImage(0, 40, bobbyicons::logo.WIDTH, bobbyicons::logo.HEIGHT, bobbyicons::logo.buffer);
    espgui::tft.setSwapBytes(false);
    tft.drawString("Bobbycar-OS", 32, 200);
    tft.drawString("booting...", 32, 225);
    tft.setTextFont(2);
    tft.drawString("last reboot reason:", 32, 275);
    tft.drawString(espcpputils::toString(esp_reset_reason()), 32, 295);
    tft.setTextFont(4);
    bootLabel.start();
}

void updateDisplay()
{
    if (currentDisplay)
        currentDisplay->update();

    if (changeScreenCallback)
    {
        changeScreenCallback();
        changeScreenCallback = {};
    }
}

void redrawDisplay()
{
    if (currentDisplay)
    {
        currentDisplay->redraw();
    }
}
