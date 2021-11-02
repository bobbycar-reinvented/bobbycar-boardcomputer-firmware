#pragma once

// 3rdparty lib includes
#include "menudisplay.h"

// local includes
#include "texts.h"

class BuzzerMenu :
    public espgui::MenuDisplay,
    public espgui::StaticText<TEXT_BUZZER>
{
public:
    BuzzerMenu();

    void back() override;
};
