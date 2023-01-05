#include "defaultstatusdisplay.h"

// 3rdparty lib includes
#include <screenmanager.h>

// local includes
#include "newsettings.h"
#include "screens/batteryinfodisplay.h"
#include "screens/metersdisplay.h"
#include "screens/speedinfodisplay.h"
#include "screens/statusdisplay.h"

void switchToDefaultStatusDisplay()
{
    switch (configs.defaultStatusDisplay.value())
    {
    case DefaultStatusDisplay::Default:
        espgui::switchScreen<bobby::StatusDisplay>();
        break;
    case DefaultStatusDisplay::Meters:
        espgui::switchScreen<bobby::MetersDisplay>();
        break;
    case DefaultStatusDisplay::Battery:
        espgui::switchScreen<bobby::BatteryInfoDisplay>();
        break;
    case DefaultStatusDisplay::BetterStatus:
        espgui::switchScreen<bobby::SpeedInfoDisplay>();
        break;
    default:
        espgui::switchScreen<bobby::StatusDisplay>();
        break;
    }
}

void PushDefaultStatusDisplay::triggered()
{
    switchToDefaultStatusDisplay();
}
