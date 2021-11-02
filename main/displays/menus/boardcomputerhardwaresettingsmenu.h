#pragma once

// local includes
#include "menudisplay.h"
#include "texts.h"

class BoardcomputerHardwareSettingsMenu :
    public espgui::MenuDisplay,
    public espgui::StaticText<TEXT_BOARDCOMPUTERHARDWARESETTINGS>
{
public:
    BoardcomputerHardwareSettingsMenu();

    void back() override;
};
