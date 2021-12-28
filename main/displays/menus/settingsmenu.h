#pragma once

// local includes
#include "displays/menudisplaywithtime.h"
#include "texts.h"

class SettingsMenu :
    public bobbygui::MenuDisplayWithTime,
    public espgui::StaticText<TEXT_SETTINGS>
{
public:
    SettingsMenu();

    void back() override;
};
