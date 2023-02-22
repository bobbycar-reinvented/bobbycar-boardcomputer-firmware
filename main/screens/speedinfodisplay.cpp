#include "speedinfodisplay.h"

// 3rdparty lib includes
#include <fmt/core.h>
#include <fontrenderer.h>
#include <screenmanager.h>
#include <tftcolors.h>
#include <tftinterface.h>

// local includes
#include "drivingstatistics.h"
#include "screens/batteryinfodisplay.h"
#include "screens/mainmenu.h"
#include "screens/statusdisplay.h"
#include "taskmanager.h"

namespace bobby {
void SpeedInfoDisplay::initScreen(espgui::TftInterface &tft)
{
    Base::initScreen(tft);

    m_dischargingBar.construct(10, PROGRESS_BAR_START_Y, tft.width()/2 - 10, 25, 0, 40, TFT_GREEN);
    m_chargingBar.construct(tft.width()/2, PROGRESS_BAR_START_Y, tft.width()/2 - 10, 25, 0, 40, TFT_RED);

    m_labelSpeed.start(tft);

    m_dischargingBar->start(tft);
    m_chargingBar->start(tft);

    m_batteryPercentLabel.start(tft);
    m_voltageLabel.start(tft);
    m_distanceLabel.start(tft);
    m_currentPowerLabel.start(tft);

    m_performanceLabel.start(tft);
}

void SpeedInfoDisplay::redraw(espgui::TftInterface &tft)
{
    using namespace espgui;

    Base::redraw(tft);

    m_dischargingBar->setMinMax(0, profileSettings.limits.iDcMax * controllers.size() * 2);
    m_chargingBar->setMinMax(0, profileSettings.limits.iDcMax * controllers.size() * 2);

    auto font = espgui::FontRenderer{tft};

    font.setTextSize(4);

    m_labelSpeed.redraw(tft, font,
            std::abs(avgSpeedKmh) < 10 ? fmt::format("{:.2f}", avgSpeedKmh) :
            (std::abs(avgSpeedKmh) < 100 ? fmt::format("{:.1f}", avgSpeedKmh) : fmt::format("{:.0f}", avgSpeedKmh)), espgui::TFT_WHITE, espgui::TFT_BLACK, 4);

    font.setTextSize(1);
    m_batteryPercentLabel.redraw(tft, font, battery::getBatteryPercentageString(), espgui::TFT_WHITE, espgui::TFT_BLACK, 4);

    if (const auto avgVoltage = controllers.getAvgVoltage(); avgVoltage)
    {
        auto watt = sumCurrent * *avgVoltage;

        m_voltageLabel.redraw(tft, font, fmt::format("{:.1f} V", avgVoltage.value()), espgui::TFT_WHITE, espgui::TFT_BLACK, 4);
        font.setTextSize(2);
        m_currentPowerLabel.redraw(tft, font, fmt::format("{:.0f} W", watt), espgui::TFT_WHITE, espgui::TFT_BLACK, 4);
        font.setTextSize(1);
    }
    else
    {
        m_voltageLabel.redraw(tft, "No voltage", espgui::TFT_WHITE, espgui::TFT_BLACK, 4);
        m_currentPowerLabel.redraw(tft, "No power", espgui::TFT_WHITE, espgui::TFT_BLACK, 4);
    }

    m_distanceLabel.redraw(tft, font,
            drivingStatistics.meters_driven > 1000 ? fmt::format("{:.3f} km", drivingStatistics.meters_driven / 1000) :
            (drivingStatistics.meters_driven > 100 ? fmt::format("{:.1f} m", drivingStatistics.meters_driven) : fmt::format("{:.2f} m", drivingStatistics.meters_driven)), espgui::TFT_WHITE, espgui::TFT_BLACK, 4);

    font.setTextSize(1);

    m_dischargingBar->redraw(tft, sumCurrent < 0.f ? (-sumCurrent) : 0.f);
    m_chargingBar->redraw(tft, sumCurrent > 0.f ? sumCurrent : 0.f);

    m_performanceLabel.redraw(tft, std::to_string(drivingModeTask.callCount()), (drivingModeTask.callCount() < 35) ? espgui::TFT_ORANGE : espgui::TFT_WHITE, espgui::TFT_BLACK, 2);
}

void SpeedInfoDisplay::buttonPressed(espgui::Button button)
{
    Base::buttonPressed(button);

    switch (button)
    {
    using espgui::Button;
    case Button::Right:
        espgui::pushScreen<MainMenu>();
        break;
    case Button::Up:
        espgui::switchScreen<BatteryInfoDisplay>();
        break;
    case Button::Down:
#ifdef FEATURE_BMS
        espgui::switchScreen<BmsDisplay>();
#else
        espgui::switchScreen<StatusDisplay>();
#endif
        break;
    default:;
    }
}
} // namespace bobby
