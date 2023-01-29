#include "rebootscreen.h"

// esp-idf includes
#include <esp_system.h>

// 3rdparty lib includes
#include <fontrenderer.h>
#include <tftcolors.h>
#include <tftinterface.h>

namespace bobby {
void RebootScreen::initScreen(espgui::TftInterface &tft)
{
    Base::initScreen(tft);

    auto font = espgui::FontRenderer{tft};
    font.drawString("Rebooting...", 0, 50, espgui::TFT_WHITE, espgui::TFT_BLACK, 4);

    esp_restart();
}

std::string RebootScreen::title() const
{
    return "Reboot";
}

void RebootScreen::buttonPressed(espgui::Button button) {}
void RebootScreen::buttonReleased(espgui::Button button) {}
} // namespace bobby
