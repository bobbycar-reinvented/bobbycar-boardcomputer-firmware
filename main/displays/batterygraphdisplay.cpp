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
    const auto max_height = espgui::tft.height() - 1;
    const auto max_width = espgui::tft.width() - 4;
    const uint16_t part = max_width / points;
    const auto min_voltage = getMinBatCellVoltage(configs.battery.cellType.value);
    const auto max_voltage = getMaxBatCellVoltage(configs.battery.cellType.value);
    ESP_LOGI(TAG, "min_voltage: %f, max_voltage: %f", min_voltage, max_voltage);
    for (uint8_t i = 0; points >= i; i++) {
        // draw lines between point->minVoltage and point->maxVoltage from left to right
        if (const auto point = get_point_n_voltages(configs.battery.cellType.value, points - i); point)
        {
            const int x1 = 2 + part * (points - i + 1);
            const int y1 = float_map(point->minVoltage / 100.f, min_voltage, max_voltage, max_height, TOP_OFFSET);
            const int x2 = 2 + part * (points - i);
            const int y2 = float_map(point->maxVoltage / 100.f, min_voltage, max_voltage, max_height, TOP_OFFSET);
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
