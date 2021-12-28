#pragma once

// local includes
#include "displays/bobbymenudisplay.h"
#include "texts.h"

class ControllerHardwareSettingsMenu :
    public BobbyMenuDisplay,
    public espgui::StaticText<TEXT_CONTROLLERHARDWARESETTINGS>
{
public:
    ControllerHardwareSettingsMenu();

    void back() override;
};
