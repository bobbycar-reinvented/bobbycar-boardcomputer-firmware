#pragma once

// Local includes
#include "menudisplay.h"
#include "utils.h"
#include "menuitem.h"
#include "icons/back.h"
#include "icons/settings.h"
#include "texts.h"
#include "actions/dummyaction.h"
#include "actions/switchscreenaction.h"
#include "battery.h"
#include "menus/batterymenu.h"

using namespace espgui;

namespace  {
    class CalibrateVoltageDisplay;
    class BatteryMenu;
}

namespace  {
    class CalibrateVoltageDisplay :
            public MenuDisplay,
            public StaticText<TEXT_BATTERY_CALIBRATE>,
            public BackActionInterface<SwitchScreenAction<BatteryMenu>>
    {
    public:
        CalibrateVoltageDisplay()
        {
            constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,                                                    SwitchScreenAction<BatteryMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
        }
    };
} // Namespace
