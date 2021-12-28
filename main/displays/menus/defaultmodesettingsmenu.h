#pragma once

// local includes
#include "displays/bobbymenudisplay.h"
#include "texts.h"

class DefaultModeSettingsMenu :
    public BobbyMenuDisplay,
    public espgui::StaticText<TEXT_DEFAULTMODESETTIGNS>
{
public:
    DefaultModeSettingsMenu();

    void back() override;
};
