#pragma once

// system includes
#include <esp_system.h>

// 3rdparty lib includes
#include <actioninterface.h>
#include <tftinstance.h>

// local includes
#include "newsettings.h"

template<bool reboot>
class ResetNVSAction : public virtual espgui::ActionInterface
{
public:
    void triggered() override
    {
        if (reboot)
        {
            espgui::tft.fillScreen(TFT_BLACK);
            espgui::tft.setTextColor(TFT_YELLOW);

            espgui::tft.drawString("Reboot", 5, 5, 4);

            espgui::tft.fillRect(0, 34, espgui::tft.width(), 3, TFT_WHITE);

            espgui::tft.setTextColor(TFT_WHITE);
            espgui::tft.drawString("Rebooting now...", 0, 50, 4);

            configs.reset();

            esp_restart();
        }
        else
        {
            configs.reset();
        }
    }
};
