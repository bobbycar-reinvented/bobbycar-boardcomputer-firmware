#pragma once

// 3rdparty lib includes
#include "menudisplay.h"

// local includes
#include "texts.h"

class TimeSettingsMenu :
    public espgui::MenuDisplay,
    public espgui::StaticText<TEXT_TIME>
{
public:
    TimeSettingsMenu();

    void back() override;
};
