#pragma once

// 3rdparty lib includes
#include "menudisplay.h"

// local includes
#include "texts.h"

class LimitsSettingsMenu :
    public espgui::MenuDisplay,
    public espgui::StaticText<TEXT_LIMITSSETTINGS>
{
public:
    LimitsSettingsMenu();

    void back() override;
};
