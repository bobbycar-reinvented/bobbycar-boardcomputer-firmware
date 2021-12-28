#pragma once

// local includes
#include "displays/bobbymenudisplay.h"
#include "texts.h"

class MotortestModeSettingsMenu :
    public BobbyMenuDisplay,
    public espgui::StaticText<TEXT_MOTORTESTMODESETTINGS>
{
public:
    MotortestModeSettingsMenu();

    void back() override;
};
