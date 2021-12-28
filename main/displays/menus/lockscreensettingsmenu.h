#pragma once

// local includes
#include "displays/bobbymenudisplay.h"
#include "texts.h"

class LockscreenSettingsMenu :
    public BobbyMenuDisplay,
    public espgui::StaticText<TEXT_LOCKSCREENSETTINGS>
{
public:
    LockscreenSettingsMenu();

    void back() override;
};
