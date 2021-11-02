#include "garagedisplay.h"

// system includes

// esp-idf includes
#include <esp_log.h>

// 3rdparty lib includes
#include <fmt/core.h>
#include <tftinstance.h>
#include <screenmanager.h>

// local includes
#include "displays/menus/mainmenu.h"
#include "globals.h"
#include "texts.h"

#ifdef FEATURE_GARAGE
void GarageDisplay::start()
{
}

void GarageDisplay::initScreen()
{
    espgui::tft.fillScreen(TFT_BLACK);
    espgui::tft.setTextFont(4);
    espgui::tft.setTextColor(TFT_YELLOW);

    espgui::tft.drawString(TEXT_GARAGE, 5, 5, 4);

    espgui::tft.fillRect(0, 34, espgui::tft.width(), 3, TFT_WHITE);

    espgui::tft.setTextColor(TFT_WHITE, TFT_BLACK);

    espgui::tft.drawString("Garage", 20, 100);
}

void GarageDisplay::redraw()
{
}

void GarageDisplay::confirm()
{
}

void GarageDisplay::back()
{
    espgui::switchScreen<MainMenu>();
}
#endif
