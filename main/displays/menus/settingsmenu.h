#pragma once

// 3rdparty lib includes
#include "menudisplay.h"

// local includes
#include "texts.h"

class SettingsMenu :
    public espgui::MenuDisplay,
    public espgui::StaticText<TEXT_SETTINGS>
{
public:
    SettingsMenu();

    void back() override;
};
