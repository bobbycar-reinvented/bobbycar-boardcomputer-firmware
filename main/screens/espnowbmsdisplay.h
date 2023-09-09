#pragma once

#ifdef FEATURE_ESPNOW_BMS
// 3rdparty lib includes
#include <fmt/core.h>
#include <widgets/label.h>
#include <screenmanager.h>

// local includes
#include "globals.h"
#include "bmsutils.h"
#include "guihelpers/bobbydisplay.h"

namespace bobby {

class EspNowBmsDisplay : public BobbyDisplay
{
    using Base = BobbyDisplay;

public:
    void initScreen(espgui::TftInterface &tft) override;
    void redraw(espgui::TftInterface &tft) override;

    void buttonPressed(espgui::Button button) override;

private:
    static constexpr const int OFFSET_Y = 15;
    static constexpr const int OFFSET_X = 10;
    static constexpr const int STATUS_LABEL_WIDTH = 110;
    static constexpr const int BATT_LABEL_WIDTH = 75;

    espgui::Label m_statusLabel{OFFSET_X, OFFSET_Y*1};
    espgui::Label m_voltageLabel{OFFSET_X, OFFSET_Y*2};
    espgui::Label m_averageCellVoltLabel{OFFSET_X, OFFSET_Y*3};
    espgui::Label m_socLabel{OFFSET_X, OFFSET_Y*4};
    espgui::Label m_powerLabel{OFFSET_X, OFFSET_Y*5};
    espgui::Label m_currentLabel{OFFSET_X, OFFSET_Y*6};
    espgui::Label m_minCellVoltLabel{OFFSET_X + STATUS_LABEL_WIDTH, OFFSET_Y*2};
    espgui::Label m_maxCellVoltLabel{OFFSET_X + STATUS_LABEL_WIDTH, OFFSET_Y*3};
    espgui::Label m_cellDiffVoltLabel{OFFSET_X + STATUS_LABEL_WIDTH, OFFSET_Y*4};
    espgui::Label m_mosfetTempLabel{OFFSET_X + STATUS_LABEL_WIDTH, OFFSET_Y*5};
    espgui::Label m_balTempLabel{OFFSET_X + STATUS_LABEL_WIDTH, OFFSET_Y * 6};

    std::array<espgui::Label, 12> m_battLabels{{
       espgui::Label{OFFSET_X, OFFSET_Y* 8}, espgui::Label{OFFSET_X+BATT_LABEL_WIDTH, OFFSET_Y* 8}, espgui::Label{OFFSET_X+BATT_LABEL_WIDTH*2, OFFSET_Y* 8},
       espgui::Label{OFFSET_X, OFFSET_Y* 9}, espgui::Label{OFFSET_X+BATT_LABEL_WIDTH, OFFSET_Y* 9}, espgui::Label{OFFSET_X+BATT_LABEL_WIDTH*2, OFFSET_Y* 9},
       espgui::Label{OFFSET_X, OFFSET_Y*10}, espgui::Label{OFFSET_X+BATT_LABEL_WIDTH, OFFSET_Y*10}, espgui::Label{OFFSET_X+BATT_LABEL_WIDTH*2, OFFSET_Y*10},
       espgui::Label{OFFSET_X, OFFSET_Y*11}, espgui::Label{OFFSET_X+BATT_LABEL_WIDTH, OFFSET_Y*11}, espgui::Label{OFFSET_X+BATT_LABEL_WIDTH*2, OFFSET_Y*11}
    }};

    espgui::Label m_battery_state{OFFSET_X, OFFSET_Y*13};
    espgui::Label m_chargemos_state{OFFSET_X, OFFSET_Y*14};
    espgui::Label m_dischargemos_state{OFFSET_X, OFFSET_Y*15};
    espgui::Label m_balancing_state{OFFSET_X, OFFSET_Y*16};
};

} // namespace bobby
#endif // FEATURE_ESPNOW_BMS
