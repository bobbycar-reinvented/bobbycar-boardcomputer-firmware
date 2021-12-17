#pragma once

// 3rdparty lib includes
#include "widgets/menudisplaywithtime.h"
#include <menuitem.h>

// Local includes
#include "texts.h"

class StatisticsMenu :
    public bobbygui::MenuDisplayWithTime,
    public espgui::StaticText<TEXT_STATISTICSMENU>
{
public:
    StatisticsMenu();

    void back() override;
};
