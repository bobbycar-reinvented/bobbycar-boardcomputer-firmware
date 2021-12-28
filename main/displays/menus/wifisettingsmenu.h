#pragma once

// local includes
#include "displays/bobbymenudisplay.h"
#include "texts.h"

class WifiSettingsMenu :
    public BobbyMenuDisplay,
    public espgui::StaticText<TEXT_WIFISETTINGS>
{
public:
    WifiSettingsMenu();

    void back() override;
};
