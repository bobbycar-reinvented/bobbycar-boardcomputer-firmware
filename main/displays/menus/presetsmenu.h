#pragma once

// local includes
#include "displays/bobbymenudisplay.h"
#include "texts.h"

class PresetsMenu :
    public BobbyMenuDisplay,
    public espgui::StaticText<TEXT_PRESETS>
{
public:
    PresetsMenu();
    void back() override;
};
