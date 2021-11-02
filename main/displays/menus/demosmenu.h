#pragma once

// 3rdparty lib includes
#include "menudisplay.h"

// local includes
#include "texts.h"

class DemosMenu :
    public espgui::MenuDisplay,
    public espgui::StaticText<TEXT_DEMOS>
{
public:
    DemosMenu();

    void back() override;
};
