#pragma once

// system includes

// esp-idf includes
#include <esp_log.h>

// 3rdparty lib includes
#include <fmt/core.h>

// local includes
#include "display.h"
#include "actions/switchscreenaction.h"
#include "globals.h"
#include "texts.h"
#include "widgets/label.h"

namespace {
#ifdef FEATURE_GARAGE
class GarageDisplay : public Display, public BackActionInterface<SwitchScreenAction<MainMenu>>
{
public:
    void start() override;
    void initScreen() override;
    void redraw() override;
    void confirm() override;

private:
};

void GarageDisplay::start()
{
}

void GarageDisplay::initScreen()
{
    tft.fillScreen(TFT_BLACK);
    tft.setTextFont(4);
    tft.setTextColor(TFT_YELLOW);

    tft.drawString(TEXT_GARAGE, 5, 5, 4);

    tft.fillRect(0, 34, tft.width(), 3, TFT_WHITE);

    tft.setTextColor(TFT_WHITE, TFT_BLACK);

    tft.drawString("Garage", 20, 100);
}

void GarageDisplay::redraw()
{
}

void GarageDisplay::confirm()
{
}
#endif
}
