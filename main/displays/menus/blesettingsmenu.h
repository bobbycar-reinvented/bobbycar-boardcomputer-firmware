#pragma once

// local includes
#include "displays/bobbymenudisplay.h"
#include "texts.h"

#ifdef FEATURE_BLE

class BleSettingsMenu :
    public BobbyMenuDisplay,
    public espgui::StaticText<TEXT_BLESETTINGS>
{
public:
    BleSettingsMenu();
    void back() override;
};
#endif
