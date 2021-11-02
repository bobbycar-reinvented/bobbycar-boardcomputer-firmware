#pragma once

// 3rdparty lib includes
#include "menudisplay.h"

// local includes
#include "texts.h"

class SelectModeMenu :
    public espgui::MenuDisplay,
    public espgui::StaticText<TEXT_SELECTMODE>
{
    using Base = espgui::MenuDisplay;

public:
    SelectModeMenu();

    void start() override;
    void back() override;
};
