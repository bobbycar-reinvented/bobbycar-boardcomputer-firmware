#pragma once

// 3rdparty lib includes
#include "menudisplay.h"

// local includes
#include "texts.h"

class DebugMenu :
    public espgui::MenuDisplay,
    public espgui::StaticText<TEXT_DEBUG>
{
public:
    DebugMenu();

    void back() override;
};
