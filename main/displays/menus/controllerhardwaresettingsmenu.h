#pragma once

// 3rdparty lib includes
#include "menudisplay.h"

// local includes
#include "texts.h"

class ControllerHardwareSettingsMenu :
    public espgui::MenuDisplay,
    public espgui::StaticText<TEXT_CONTROLLERHARDWARESETTINGS>
{
public:
    ControllerHardwareSettingsMenu();

    void back() override;
};
