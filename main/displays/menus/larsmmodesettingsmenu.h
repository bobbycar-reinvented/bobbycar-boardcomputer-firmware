#pragma once

// 3rdparty lib includes

// local includes
#include "menudisplay.h"
#include "texts.h"

class LarsmModeSettingsMenu :
    public espgui::MenuDisplay,
    public espgui::StaticText<TEXT_LARSMMODESETTINGS>
{
public:
    LarsmModeSettingsMenu();

    void back() override;
};
