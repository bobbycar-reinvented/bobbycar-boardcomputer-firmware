#pragma once

// local includes
#include "displays/bobbymenudisplay.h"
#include "texts.h"

class BoardcomputerHardwareSettingsMenu :
    public BobbyMenuDisplay,
    public espgui::StaticText<TEXT_BOARDCOMPUTERHARDWARESETTINGS>
{
public:
    BoardcomputerHardwareSettingsMenu();

    void back() override;
};
