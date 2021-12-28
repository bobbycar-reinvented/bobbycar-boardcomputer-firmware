#pragma once

// local includes
#include "displays/bobbymenudisplay.h"
#include "texts.h"

class LimitsSettingsMenu :
    public BobbyMenuDisplay,
    public espgui::StaticText<TEXT_LIMITSSETTINGS>
{
public:
    LimitsSettingsMenu();

    void back() override;
};
