#include "batterygraphdisplay.h"
constexpr const char * const TAG = "BatteryGraphDisplay";

// 3rdparty lib includes
#include <screenmanager.h>
#include <tftinstance.h>

// local includes
#include "battery.h"
#include "globals.h"
#include "displays/menus/batterymenu.h"
#include "newsettings.h"

namespace {
    constexpr char TEXT_BATTERY_GRAPH[] = "Battery Level";
    constexpr const uint8_t TOP_OFFSET = 40;
} // namespace

void BatteryGraphDisplay::initScreen()
{
    Base::initScreen();
    const auto points = count_curve_points(configs.battery.cellType.value);
    ESP_LOGI(TAG, "Battery graph points: %d, cell type: %s", points, toString(configs.battery.cellType.value).c_str());
    const auto available_space = espgui::tft.height() - TOP_OFFSET;
    const uint16_t onePercent = espgui::tft.width() / 100;
    for (uint8_t i = 0; points >= i; i++) {
        // draw lines between point->minVoltage and point->maxVoltage from left to right
        if (const auto point = get_point_n_voltages(configs.battery.cellType.value, points - i); point)
        {
            // draw line between minVoltage and maxVoltage of point. When implemented, please contact @CommanderRedYT so that he can move and optimize the code
        }
    }
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

        const uint16_t onePercent = tft.width() / 100;
        const uint16_t xOffset = onePercent * getBatteryPercentage(*avgVoltage, cellType);
        const uint16_t lastXOffset = onePercent * getBatteryPercentage(m_lastBatVoltage, cellType);

        // clear the old one and draw the new one
        tft.fillRect(lastXOffset, TOP_OFFSET, onePercent, tft.height() - TOP_OFFSET, TFT_BLACK);
        tft.fillRect(xOffset, TOP_OFFSET, onePercent, tft.height() - TOP_OFFSET, TFT_WHITE);
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
