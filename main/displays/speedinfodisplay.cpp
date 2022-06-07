#include "speedinfodisplay.h"

// 3rdparty lib includes
#include <screenmanager.h>

// local includes
#include "displays/batteryinfodisplay.h"
#include "displays/menus/mainmenu.h"
#include "displays/statusdisplay.h"

void SpeedInfoDisplay::initScreen()
{
    Base::initScreen();
}

void SpeedInfoDisplay::redraw()
{
    Base::redraw();
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
