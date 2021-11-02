#pragma once

// 3rdparty lib includes
#include <menudisplay.h>
#include <menuitem.h>
#include <icons/back.h>
#include <actions/dummyaction.h>
#include <actions/switchscreenaction.h>

// Local includes
#include "utils.h"
#include "icons/settings.h"
#include "texts.h"
#include "battery.h"
#include "selectbatterytypemenu.h"

class BatteryMenu :
    public espgui::MenuDisplay,
    public espgui::StaticText<TEXT_BATTERY>
{
public:
    BatteryMenu();

    void back() override;
};
