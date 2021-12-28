#pragma once

// local includes
#include "displays/bobbymenudisplay.h"
#include "texts.h"

class TempomatModeSettingsMenu :
    public BobbyMenuDisplay,
    public espgui::StaticText<TEXT_TEMPOMATMODESETTINGS>
{
public:
    TempomatModeSettingsMenu();

    void back() override;
};
