#include "batterygraphdisplay.h"

// 3rdparty lib includes
#include <screenmanager.h>
#include <tftinstance.h>

// local includes
#include "battery.h"
#include "globals.h"
#include "displays/menus/batterymenu.h"

namespace {
    constexpr char TEXT_BATTERY_GRAPH[] = "Battery Level";
} // namespace

void BatteryGraphDisplay::initScreen()
{
    Base::initScreen();
}

std::string BatteryGraphDisplay::text() const
{
    return TEXT_BATTERY_GRAPH;
}

void BatteryGraphDisplay::redraw()
{
    using namespace espgui;
    Base::redraw();

    if (const auto avgVoltage = controllers.getAvgVoltage(); avgVoltage)
    {
        if (*avgVoltage == m_lastBatVoltage)
            return;
        const auto cellType = configs.battery.cellType.value;

        uint16_t onePercent = tft.width() / 100;
        uint16_t xOffset = onePercent * getBatteryPercentage(*avgVoltage, cellType);
        uint16_t lastXOffset = onePercent * getBatteryPercentage(m_lastBatVoltage, cellType);

        // clear the old one and draw the new one
        tft.fillRect(lastXOffset, 40, onePercent, tft.height() - 40, TFT_BLACK);
        tft.fillRect(xOffset, 40, onePercent, tft.height() - 40, TFT_WHITE);
        m_lastBatVoltage = *avgVoltage;
    }

    // tft.drawLine() code
}

void BatteryGraphDisplay::buttonPressed(espgui::Button button)
{
    Base::buttonPressed(button);

    switch (button)
    {
        using espgui::Button;
        case Button::Left:
        case Button::Right:
            espgui::switchScreen<BatteryMenu>();
            break;
        default:;
    }
}
