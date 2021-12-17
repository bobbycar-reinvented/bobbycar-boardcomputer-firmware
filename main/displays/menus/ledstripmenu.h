#pragma once

// 3rdparty lib includes
#include "widgets/menudisplaywithtime.h"

// local includes
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
