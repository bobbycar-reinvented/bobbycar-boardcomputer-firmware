#pragma once

// 3rdparty lib includes
#include "menudisplay.h"

// local includes
#include "texts.h"

class WifiSettingsMenu :
    public espgui::MenuDisplay,
    public espgui::StaticText<TEXT_WIFISETTINGS>
{
public:
    WifiSettingsMenu();

    void back() override;
};
