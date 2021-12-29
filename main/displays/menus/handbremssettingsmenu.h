#pragma once

// local includes
#include "displays/bobbymenudisplay.h"
#include "texts.h"

class HandbremsSettingsMenu :
    public BobbyMenuDisplay,
    public espgui::StaticText<TEXT_HANDBREMSE>
{
public:
    HandbremsSettingsMenu();
    void back() override;
};
