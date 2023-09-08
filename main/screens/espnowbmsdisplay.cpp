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

    FontRenderer fontRenderer{tft};

    fontRenderer.drawString("Voltage:", 15, m_voltageLabel.y(), espgui::TFT_WHITE, espgui::TFT_BLACK, 4);
    m_voltageLabel.start(tft);

    fontRenderer.drawString("AvgCell:", 15, m_averageCellVoltLabel.y(), espgui::TFT_WHITE, espgui::TFT_BLACK, 4);
    m_averageCellVoltLabel.start(tft);

    fontRenderer.drawString("SOC:", 15, m_socLabel.y(), espgui::TFT_WHITE, espgui::TFT_BLACK, 4);
    m_socLabel.start(tft);

    fontRenderer.drawString("Power:", 15, m_powerLabel.y(), espgui::TFT_WHITE, espgui::TFT_BLACK, 4);
    m_powerLabel.start(tft);

    fontRenderer.drawString("Current:", 15, m_currentLabel.y(), espgui::TFT_WHITE, espgui::TFT_BLACK, 4);
    m_currentLabel.start(tft);

    for (auto &label: m_battLabels)
        label.start(tft);

    m_battery_state.start(tft);
    m_chargemos_state.start(tft);
    m_dischargemos_state.start(tft);
}

void EspNowBmsDisplay::redraw(espgui::TftInterface &tft)
{
    Base::redraw(tft);

    bool hasData = espnowbms::ant_bms_data.last_update.has_value();

    m_statusLabel.redraw(tft, hasData ? "OK" : "FAIL", hasData ? espgui::TFT_GREEN : espgui::TFT_RED, espgui::TFT_BLACK, 2);

    if (hasData)
    {
        m_voltageLabel.redraw(tft, fmt::format("{:.02f}V", espnowbms::ant_bms_data.total_voltage), espgui::TFT_WHITE, espgui::TFT_BLACK, 2);
        m_averageCellVoltLabel.redraw(tft, fmt::format("{:.02f} V", espnowbms::ant_bms_data.average_cell_voltage), espgui::TFT_WHITE, espgui::TFT_BLACK, 2);
        m_socLabel.redraw(tft, fmt::format("{:.02f}%", espnowbms::ant_bms_data.state_of_charge), espgui::TFT_WHITE, espgui::TFT_BLACK, 2);
        m_powerLabel.redraw(tft, fmt::format("{:.02f}W", espnowbms::ant_bms_data.power), espgui::TFT_WHITE, espgui::TFT_BLACK, 2);
        m_currentLabel.redraw(tft, fmt::format("{:.02f}A", espnowbms::ant_bms_data.current), espgui::TFT_WHITE, espgui::TFT_BLACK, 2);

        m_battery_state.redraw(tft, fmt::format("Batt: {}", espnowbms::ant_bms_data.battery_status_string), espgui::TFT_WHITE, espgui::TFT_BLACK, 2);
        m_chargemos_state.redraw(tft, fmt::format("Charge: {}", espnowbms::ant_bms_data.charge_mosfet_status_string), espgui::TFT_WHITE, espgui::TFT_BLACK, 2);
        m_dischargemos_state.redraw(tft, fmt::format("Discharge: {}", espnowbms::ant_bms_data.discharge_mosfet_status_string), espgui::TFT_WHITE, espgui::TFT_BLACK, 2);
        m_balancing_state.redraw(tft, fmt::format("Balance: {}", espnowbms::ant_bms_data.balancer_status_string), espgui::TFT_WHITE, espgui::TFT_BLACK, 2);
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
            for (auto &v: espnowbms::ant_bms_data.cell_voltages)
                highest = std::max(highest, v);
            return highest;
        }();

        float lowestVoltage = [&](){
            float lowest = 1000;
            for (auto &v: espnowbms::ant_bms_data.cell_voltages)
                lowest = std::min(lowest, v);
            return lowest;
        }();

        for (int i = 0; i < m_battLabels.size(); i++)
        {
            if (espnowbms::ant_bms_data.cell_voltages.size() <= i)
                break;

            auto value = espnowbms::ant_bms_data.cell_voltages[i];

            bool isHighest = value == highestVoltage;
            bool isLowest = value == lowestVoltage;
            bool isBalancing = espnowbms::ant_bms_data.balanced_cell_bitmask & (1 << i);

            uint16_t color = espgui::TFT_WHITE;
            uint16_t bgColor = espgui::TFT_BLACK;

            // if highest, textColor should be green. if lowest, textColor should be red. if balancing, background should be white. if not balancing, background should be black.
            if (isHighest)
                color = espgui::TFT_GREEN;
            else if (isLowest)
                color = espgui::TFT_RED;

            if (isBalancing)
            {
                bgColor = espgui::TFT_WHITE;
                if (!isHighest && !isLowest)
                    color = espgui::TFT_BLACK;
            }

            m_battLabels[i].redraw(tft, fmt::format("{:.03f}V", espnowbms::ant_bms_data.cell_voltages[i]), color, bgColor, 2);
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
