#pragma once

// 3rdparty lib includes
#include "menudisplay.h"

// local includes
#include "texts.h"

class StationWifiSettingsMenu :
    public espgui::MenuDisplay,
    public espgui::StaticText<TEXT_STATIONWIFISETTINGS>
{
public:
    StationWifiSettingsMenu();

    void back() override;
};
