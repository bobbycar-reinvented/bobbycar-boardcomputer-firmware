#pragma once

// 3rdparty lib includes
#include "menudisplay.h"

// local includes
#include "texts.h"

class TempomatModeSettingsMenu :
    public espgui::MenuDisplay,
    public espgui::StaticText<TEXT_TEMPOMATMODESETTINGS>
{
public:
    TempomatModeSettingsMenu();

    void back() override;
};
