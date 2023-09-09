#include "espnowbmsdisplay.h"

#ifdef FEATURE_ESPNOW_BMS

// 3rdparty lib includes
#include <screenmanager.h>
#include <fontrenderer.h>

// local includes
#include "screens/mainmenu.h"
#include "screens/speedinfodisplay.h"
#include "screens/statusdisplay.h"
#include "guihelpers/bobbymenudisplay.h"
#include "espnowbms.h"

namespace bobby {

using namespace espgui;

void EspNowBmsDisplay::initScreen(espgui::TftInterface &tft)
{
    Base::initScreen(tft);

    tft.fillScreen(espgui::TFT_BLACK);

    m_statusLabel.start(tft);
    m_statusLabel.redraw(tft, "init", espgui::TFT_WHITE, espgui::TFT_BLACK, 2);

    m_voltageLabel.start(tft);
    m_averageCellVoltLabel.start(tft);
    m_socLabel.start(tft);
    m_powerLabel.start(tft);
    m_currentLabel.start(tft);

    m_minCellVoltLabel.start(tft);
    m_maxCellVoltLabel.start(tft);
    m_cellDiffVoltLabel.start(tft);
    m_mosfetTempLabel.start(tft);
    m_balTempLabel.start(tft);

    for (auto &label: m_battLabels)
        label.start(tft);

    m_battery_state.start(tft);
    m_chargemos_state.start(tft);
    m_dischargemos_state.start(tft);
}

void EspNowBmsDisplay::redraw(espgui::TftInterface &tft)
{
    using namespace espnowbms;
    Base::redraw(tft);

    bool hasData = ant_bms_data && ant_bms_data->last_update.has_value();

    m_statusLabel.redraw(tft, hasData ? "OK" : "FAIL", hasData ? espgui::TFT_GREEN : espgui::TFT_RED, espgui::TFT_BLACK, 2);

    if (hasData)
    {
        using namespace std::chrono_literals;

        m_voltageLabel.redraw(tft, fmt::format("Voltage: {:.02f}V", ant_bms_data->total_voltage), espgui::TFT_WHITE, espgui::TFT_BLACK, 2);
        m_averageCellVoltLabel.redraw(tft, fmt::format("AvgCell: {:.02f} V", ant_bms_data->average_cell_voltage), espgui::TFT_WHITE, espgui::TFT_BLACK, 2);
        m_socLabel.redraw(tft, fmt::format("SoC: {:.02f}%", ant_bms_data->state_of_charge), espgui::TFT_WHITE, espgui::TFT_BLACK, 2);
        m_powerLabel.redraw(tft, fmt::format("Power: {:.1f}W", ant_bms_data->power), espgui::TFT_WHITE, espgui::TFT_BLACK, 2);
        m_currentLabel.redraw(tft, fmt::format("Current: {:.2f}A", ant_bms_data->current), espgui::TFT_WHITE, espgui::TFT_BLACK, 2);

        m_minCellVoltLabel.redraw(tft, fmt::format("MinCell: {:.03f}V", ant_bms_data->min_cell_voltage), espgui::TFT_WHITE, espgui::TFT_BLACK, 2);
        m_maxCellVoltLabel.redraw(tft, fmt::format("MaxCell: {:.03f}V", ant_bms_data->max_cell_voltage), espgui::TFT_WHITE, espgui::TFT_BLACK, 2);
        m_cellDiffVoltLabel.redraw(tft, fmt::format("CellDiff: {:.03f}V", ant_bms_data->max_cell_voltage - ant_bms_data->min_cell_voltage), espgui::TFT_WHITE, espgui::TFT_BLACK, 2);
        m_mosfetTempLabel.redraw(tft, fmt::format("MosfTemp: {:.1f}°C", ant_bms_data->mosfet_temperature), espgui::TFT_WHITE, espgui::TFT_BLACK, 2);
        m_balTempLabel.redraw(tft, fmt::format("BalTemp: {:.1f}°C", ant_bms_data->balancer_temperature), espgui::TFT_WHITE, espgui::TFT_BLACK, 2);

        m_battery_state.redraw(tft, fmt::format("Batt: {} LastUpdate: {}ms", ant_bms_data->battery_status_string, ant_bms_data->last_update.has_value() ? espchrono::ago(*ant_bms_data->last_update) / 1ms : 0), espgui::TFT_WHITE, espgui::TFT_BLACK, 2);
        m_chargemos_state.redraw(tft, fmt::format("Charge: {} Time: {}", ant_bms_data->charge_mosfet_status_string, ant_bms_data->accumulated_charging_time_formatted), espgui::TFT_WHITE, espgui::TFT_BLACK, 2);
        m_dischargemos_state.redraw(tft, fmt::format("Discharge: {} Time: {}", ant_bms_data->discharge_mosfet_status_string, ant_bms_data->accumulated_discharging_time_formatted), espgui::TFT_WHITE, espgui::TFT_BLACK, 2);
        m_balancing_state.redraw(tft, fmt::format("Balance: {}", ant_bms_data->balancer_status_string), espgui::TFT_WHITE, espgui::TFT_BLACK, 2);
    }
    else
    {
        m_voltageLabel.clear(tft, espgui::TFT_BLACK);
        m_averageCellVoltLabel.clear(tft, espgui::TFT_BLACK);
        m_socLabel.clear(tft, espgui::TFT_BLACK);
        m_powerLabel.clear(tft, espgui::TFT_BLACK);
        m_currentLabel.clear(tft, espgui::TFT_BLACK);
    }

    if (hasData)
    {
        float highestVoltage = [&](){
            float highest = 0;
            for (auto &v: ant_bms_data->cell_voltages)
                highest = std::max(highest, v);
            return highest;
        }();

        float lowestVoltage = [&](){
            float lowest = 1000;
            for (auto &v: ant_bms_data->cell_voltages)
                lowest = std::min(lowest, v);
            return lowest;
        }();

        for (int i = 0; i < m_battLabels.size(); i++)
        {
            if (ant_bms_data->cell_voltages.size() <= i)
                break;

            auto value = ant_bms_data->cell_voltages[i];

            bool isHighest = value == highestVoltage;
            bool isLowest = value == lowestVoltage;

            std::string color = "&6";

            // if highest, textColor should be green. if lowest, textColor should be red. if balancing, background should be white. if not balancing, background should be black.
            if (isHighest)
                color = "&2";
            else if (isLowest)
                color = "&1";

            m_battLabels[i].redraw(tft, fmt::format("{}{}&c:{:.03f}V", color, i, ant_bms_data->cell_voltages[i]), espgui::TFT_WHITE, espgui::TFT_BLACK, 2);
        }
    }
    else
    {
        for (auto &label: m_battLabels)
            label.clear(tft, espgui::TFT_BLACK);
    }
}

void EspNowBmsDisplay::buttonPressed(espgui::Button button)
{
    Base::buttonPressed(button);

    switch (button)
    {
        using espgui::Button;
    case Button::Right:
        pushScreen<MainMenu>();
        break;
    case Button::Up:
        switchScreen<SpeedInfoDisplay>();
        break;
    case Button::Down:
        switchScreen<StatusDisplay>();
        break;
    default:;
    }
}

} // namespace bobby
#endif // FEATURE_ESPNOW_BMS
