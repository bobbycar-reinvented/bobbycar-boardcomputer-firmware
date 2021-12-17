#pragma once

// local includes
#include "menudisplay.h"
#include "texts.h"

class AccessPointWifiSettingsMenu :
    public espgui::MenuDisplay,
    public espgui::StaticText<TEXT_ACCESSPOINTWIFISETTINGS>
{
public:
    AccessPointWifiSettingsMenu();
    void back() override;
};
