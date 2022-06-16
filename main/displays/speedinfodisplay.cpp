#include "speedinfodisplay.h"

// 3rdparty lib includes
#include <fmt/core.h>
#include <screenmanager.h>

// local includes
#include "displays/batteryinfodisplay.h"
#include "displays/menus/mainmenu.h"
#include "displays/statusdisplay.h"

void SpeedInfoDisplay::initScreen()
{
    Base::initScreen();

    m_labelSpeed.start();

    m_dischargingBar.start();
    m_chargingBar.start();
}

void SpeedInfoDisplay::redraw()
{
    using namespace espgui;

    Base::redraw();

    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextFont(4);

    tft.setTextSize(3);

    m_labelSpeed.redraw(fmt::format(avgSpeedKmh < 10 ? "{:.3f}" : "{:.1f}", avgSpeedKmh));

    tft.setTextSize(1);

    m_dischargingBar.redraw(sumCurrent<0.f?(-sumCurrent):0.f);
    m_chargingBar.redraw(sumCurrent>0.f?sumCurrent:0.f);
}

void SpeedInfoDisplay::buttonPressed(espgui::Button button)
{
    Base::buttonPressed(button);

    switch (button) {
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
