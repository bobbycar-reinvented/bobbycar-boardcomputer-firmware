#pragma once

// local includes
#include "displays/menudisplaywithtime.h"
#include "texts.h"

#ifdef FEATURE_LEDSTRIP
class LedstripMenu :
    public bobbygui::MenuDisplayWithTime,
    public espgui::StaticText<TEXT_LEDSTRIP>
{
public:
    LedstripMenu();

    void back() override;
};
#endif
