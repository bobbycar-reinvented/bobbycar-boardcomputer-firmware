#include "batterygraphdisplay.h"
constexpr const char * const TAG = "BatteryGraphDisplay";

// 3rdparty lib includes
#include <screenmanager.h>
#include <tftinstance.h>

// local includes
#include "battery.h"
#include "displays/menus/batterymenu.h"
#include "globals.h"
#include "newsettings.h"
#include "utils.h"

namespace {
    constexpr char TEXT_BATTERY_GRAPH[] = "Battery Level";
    constexpr const uint8_t TOP_OFFSET = 40;
} // namespace

void BatteryGraphDisplay::initScreen()
{
    Base::initScreen();
    const auto points = count_curve_points(configs.battery.cellType.value);
    ESP_LOGI(TAG, "Battery graph points: %d, cell type: %s", points, toString(configs.battery.cellType.value).c_str());
    const auto max_height = espgui::tft.height() - TOP_OFFSET;
    const auto max_width = espgui::tft.width();
    const uint16_t part = max_width / points;
    for (uint8_t i = 0; points >= i; i++) {
        // draw lines between point->minVoltage and point->maxVoltage from left to right
        if (const auto point = get_point_n_voltages(configs.battery.cellType.value, points - i); point)
        {
            // TODO: Fix float_map to not be broken
            // Current output: float_map(335, 2.55, 4.5, 0, 280) = 47736
            const int x1 = part * i;
            const int y1 = float_map(point->minVoltage, 2.55, 4.5, 0, max_height);
            const int x2 = part * (i + 1);
            const int y2 = float_map(point->maxVoltage, 2.55, 4.5, 0, max_height);
            espgui::tft.drawLine(x1, y1, x2, y2, TFT_WHITE);
            ESP_LOGI(TAG, "espgui::tft.drawLine(%d, %d, %d, %d, TFT_WHITE);", x1, y1, x2, y2);
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
