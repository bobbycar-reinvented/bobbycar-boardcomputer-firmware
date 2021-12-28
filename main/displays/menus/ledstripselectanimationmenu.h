#pragma once

// Local includes
#include "displays/bobbymenudisplay.h"
#include "texts.h"

#ifdef FEATURE_LEDSTRIP
class LedstripSelectAnimationMenu :
    public BobbyMenuDisplay,
    public espgui::StaticText<TEXT_SELECTANIMATION>
{
public:
    LedstripSelectAnimationMenu();
    void back() override;
};
#endif
