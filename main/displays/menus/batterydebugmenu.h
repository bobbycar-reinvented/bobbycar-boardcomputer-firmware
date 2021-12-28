#pragma once

// 3rdparty lib includes
#include <menuitem.h>
#include <icons/back.h>
#include <actions/dummyaction.h>
#include <actions/switchscreenaction.h>

// Local includes
#include "displays/bobbymenudisplay.h"
#include "utils.h"
#include "icons/settings.h"
#include "texts.h"
#include "battery.h"

class BatteryDebugMenu :
    public BobbyMenuDisplay,
    public espgui::StaticText<TEXT_BATTERYDEBUG>
{
public:
    BatteryDebugMenu();

    void back() override;
};
