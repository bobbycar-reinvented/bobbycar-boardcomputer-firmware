#pragma once

// local includes
#include "displays/bobbymenudisplay.h"
#include "texts.h"

class ModesSettingsMenu :
    public BobbyMenuDisplay,
    public espgui::StaticText<TEXT_MODESSETTINGS>
{
public:
    ModesSettingsMenu();

    void back() override;
};
