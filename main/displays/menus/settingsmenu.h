#pragma once

// 3rdparty lib includes
#include "widgets/menudisplaywithtime.h"

// local includes
#include "texts.h"

class SettingsMenu :
    public bobbygui::MenuDisplayWithTime,
    public espgui::StaticText<TEXT_SETTINGS>
{
public:
    SettingsMenu();

    void back() override;
};
