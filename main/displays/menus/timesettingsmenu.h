#pragma once

// local includes
#include "displays/menudisplaywithtime.h"
#include "texts.h"

class TimeSettingsMenu :
    public bobbygui::MenuDisplayWithTime,
    public espgui::StaticText<TEXT_TIME>
{
public:
    TimeSettingsMenu();

    void back() override;
};
