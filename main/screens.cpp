#include "screens.h"

// 3rdparty lib includes
#include <tftinstance.h>
#include <screenmanager.h>

// local includes
#include "globals.h"
#include "utils.h"
#include "icons/logo.h"
#include "buttons.h"

using namespace espgui;

Label bootLabel{32, 250};

void initScreen()
{
    tft.init();
    tft.fillScreen(TFT_WHITE);
    tft.setTextColor(TFT_BLACK, TFT_WHITE);
    tft.setTextFont(4);
    tft.pushImage(0, 40, bobbyicons::logo.WIDTH, bobbyicons::logo.HEIGHT, bobbyicons::logo.buffer);
    tft.drawString("Bobbycar-OS", 32, 200);
    tft.drawString("booting...", 32, 225);
    bootLabel.start();
}

void updateDisplay()
{
    if (rotated)
    {
        const auto rotatedCopy = rotated;
        rotated = 0;

        if (currentDisplay)
        {
            if (rotatedCopy < 0)
                currentDisplay->buttonPressed(espgui::Button::Up);
            else
                currentDisplay->buttonPressed(espgui::Button::Down);
        }
    }

    if (requestFullRedraw)
    {
        requestFullRedraw = false;

        tft.init();

        if (currentDisplay)
            currentDisplay->initScreen();
    }

    if (confirmButtonPressed)
    {
        confirmButtonPressed = false;

        if (currentDisplay)
            currentDisplay->buttonPressed(espgui::Button::Right);
    }

    if (confirmButtonLongPressed)
    {
        confirmButtonLongPressed = false;
        //Serial.println("todo: implement long press for confirm");
    }

    if (backButtonPressed)
    {
        backButtonPressed = false;

        if (currentDisplay)
            currentDisplay->buttonPressed(espgui::Button::Left);
    }

    if (backButtonLongPressed)
    {
        backButtonLongPressed = false;
        //Serial.println("todo: implement long press for back");
    }

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
