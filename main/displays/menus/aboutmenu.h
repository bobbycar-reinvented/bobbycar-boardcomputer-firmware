#pragma once

// 3rdparty lib includes
#include <menudisplay.h>

// local includes
#include "texts.h"

class AboutMenu :
    public espgui::MenuDisplay,
    public espgui::StaticText<TEXT_ABOUT>
{
public:
    AboutMenu();

    void back() override;
};
