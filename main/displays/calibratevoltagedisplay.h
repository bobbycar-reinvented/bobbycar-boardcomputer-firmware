#pragma once

// 3rdparty lib includes
#include <menuitem.h>
#include <icons/back.h>
#include <actions/dummyaction.h>
#include <actions/switchscreenaction.h>
#include <widgets/label.h>

// Local includes
#include "bobbymenudisplay.h"
#include "utils.h"
#include "icons/settings.h"
#include "texts.h"
#include "battery.h"
#include "menus/batterymenu.h"
#include "globals.h"

class CalibrateVoltageDisplay :
    public BobbyMenuDisplay,
    public espgui::StaticText<TEXT_BATTERY_CALIBRATE>
{
public:
    CalibrateVoltageDisplay();

    void back() override;
};
