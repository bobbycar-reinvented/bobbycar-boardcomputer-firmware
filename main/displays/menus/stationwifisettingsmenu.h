#pragma once

// local includes
#include "displays/bobbymenudisplay.h"
#include "texts.h"

class StationWifiSettingsMenu :
    public BobbyMenuDisplay,
    public espgui::StaticText<TEXT_STATIONWIFISETTINGS>
{
public:
    StationWifiSettingsMenu();

    void back() override;
};
