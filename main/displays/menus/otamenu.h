#pragma once

// 3rdparty lib includes
#include "menudisplay.h"

// local includes
#include "texts.h"

class OtaMenu :
    public espgui::MenuDisplay,
    public espgui::StaticText<TEXT_UPDATE>
{
public:
    OtaMenu();

    void back() override;
};
