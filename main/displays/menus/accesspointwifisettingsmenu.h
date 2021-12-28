#pragma once

// local includes
#include "displays/bobbymenudisplay.h"
#include "texts.h"

class AccessPointWifiSettingsMenu :
    public BobbyMenuDisplay,
    public espgui::StaticText<TEXT_ACCESSPOINTWIFISETTINGS>
{
public:
    AccessPointWifiSettingsMenu();
    void back() override;
};
