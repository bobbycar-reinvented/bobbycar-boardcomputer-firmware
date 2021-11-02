#pragma once

// 3rdparty lib includes
#include "menudisplay.h"

// local includes
#include "texts.h"

class DefaultModeSettingsMenu :
    public espgui::MenuDisplay,
    public espgui::StaticText<TEXT_DEFAULTMODESETTIGNS>
{
public:
    DefaultModeSettingsMenu();

    void back() override;
};
