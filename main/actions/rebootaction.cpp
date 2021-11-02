#include "rebootaction.h"

// esp-idf includes
#include <esp_system.h>

// 3rdparty lib includes
#include <tftinstance.h>

// local includes
#include "globals.h"
#include "texts.h"

void RebootAction::triggered()
{
    espgui::tft.fillScreen(TFT_BLACK);
    espgui::tft.setTextColor(TFT_YELLOW);

    espgui::tft.drawString(TEXT_REBOOT, 5, 5, 4);

    espgui::tft.fillRect(0, 34, espgui::tft.width(), 3, TFT_WHITE);

    espgui::tft.setTextColor(TFT_WHITE);
    espgui::tft.drawString("Rebooting now...", 0, 50, 4);

    esp_restart();
}
