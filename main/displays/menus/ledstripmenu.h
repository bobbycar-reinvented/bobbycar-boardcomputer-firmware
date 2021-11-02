#pragma once

// 3rdparty lib includes
#include "menudisplay.h"

// local includes
#include "texts.h"

#ifdef FEATURE_LEDSTRIP
class LedstripMenu :
    public espgui::MenuDisplay,
    public espgui::StaticText<TEXT_LEDSTRIP>
{
public:
    LedstripMenu();

    void back() override;
};
#endif
