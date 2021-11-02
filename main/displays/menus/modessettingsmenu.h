#pragma once

// local includes
#include "menudisplay.h"

// local includes
#include "texts.h"

class ModesSettingsMenu :
    public espgui::MenuDisplay,
    public espgui::StaticText<TEXT_MODESSETTINGS>
{
public:
    ModesSettingsMenu();

    void back() override;
};
