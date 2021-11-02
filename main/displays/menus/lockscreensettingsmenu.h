#pragma once

// 3rdparty lib includes
#include "menudisplay.h"

// local includes
#include "texts.h"

class LockscreenSettingsMenu :
    public espgui::MenuDisplay,
    public espgui::StaticText<TEXT_LOCKSCREENSETTINGS>
{
public:
    LockscreenSettingsMenu();

    void back() override;
};
