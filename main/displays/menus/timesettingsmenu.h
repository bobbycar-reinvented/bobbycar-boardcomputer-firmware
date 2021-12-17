#pragma once

// 3rdparty lib includes
#include "widgets/menudisplaywithtime.h"

// local includes
#include "texts.h"

class TimeSettingsMenu :
    public bobbygui::MenuDisplayWithTime,
    public espgui::StaticText<TEXT_TIME>
{
public:
    TimeSettingsMenu();

    void back() override;
};
