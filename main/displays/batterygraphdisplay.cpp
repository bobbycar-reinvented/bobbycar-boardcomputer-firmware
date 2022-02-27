#include "batterygraphdisplay.h"

// 3rdparty lib includes
#include <screenmanager.h>

// local includes
#include "displays/menus/batterymenu.h"

namespace {
    constexpr char TEXT_BATTERY_GRAPH[] = "Battery Level";
} // namespace

void BatteryGraphDisplay::initScreen() {
    Base::initScreen();
}

std::string BatteryGraphDisplay::text() const {
    return TEXT_BATTERY_GRAPH;
}

void BatteryGraphDisplay::redraw() {
    Base::redraw();
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
