#pragma once

// 3rdparty lib includes
#include <menudisplay.h>
#include <menuitem.h>
#include <icons/back.h>
#include <actions/switchscreenaction.h>
#include <actioninterface.h>

// Local includes
#include "texts.h"
#include "batterymenu.h"
#include "displays/menus/mainmenu.h"

class BatteryTypeMenu :
    public espgui::MenuDisplay,
    public espgui::StaticText<TEXT_SELECT_CELL_TYPE>
{
public:
    BatteryTypeMenu();

    void back() override;
};
