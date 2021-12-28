#pragma once

// 3rdparty lib includes
#include <menuitem.h>

// Local includes
#include "displays/menudisplaywithtime.h"
#include "texts.h"

class StatisticsMenu :
    public bobbygui::MenuDisplayWithTime,
    public espgui::StaticText<TEXT_STATISTICSMENU>
{
public:
    StatisticsMenu();

    void back() override;
};
