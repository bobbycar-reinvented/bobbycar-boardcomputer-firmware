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

    espgui::Label m_statusLabel{215, 0};

    espgui::Label m_voltageLabel{123, 0};
    espgui::Label m_averageCellVoltLabel{123, 25};
    espgui::Label m_socLabel{123, 50};
    espgui::Label m_powerLabel{123, 75};
    espgui::Label m_currentLabel{123, 100};

    std::array<espgui::Label, 12> m_battLabels{{
        espgui::Label{5, 125}, espgui::Label{60, 125}, espgui::Label{120, 125}, espgui::Label{180, 125},
        espgui::Label{5, 150}, espgui::Label{60, 150}, espgui::Label{120, 150}, espgui::Label{180, 150},
        espgui::Label{5, 175}, espgui::Label{60, 175}, espgui::Label{120, 175}, espgui::Label{180, 175}
    }};

    espgui::Label m_battery_state{5, 200};
    espgui::Label m_chargemos_state{5, 225};
    espgui::Label m_dischargemos_state{5, 250};
    espgui::Label m_balancing_state{5, 275};
};

} // namespace bobby
#endif // FEATURE_ESPNOW_BMS
