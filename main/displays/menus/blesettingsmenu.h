#pragma once

// local includes
#include "menudisplay.h"
#include "texts.h"

#ifdef FEATURE_BLE

class BleSettingsMenu :
    public espgui::MenuDisplay,
    public espgui::StaticText<TEXT_BLESETTINGS>
{
public:
    BleSettingsMenu();
    void back() override;
};
#endif
