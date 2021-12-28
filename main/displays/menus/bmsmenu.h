#pragma once

#if defined(FEATURE_BLUETOOTH) && defined(FEATURE_BMS)
// local includes
#include "displays/bobbymenudisplay.h"
#include "texts.h"

class BmsMenu :
    public BobbyMenuDisplay,
    public espgui::StaticText<TEXT_BMS>
{
public:
    BmsMenu();
    void back() override;
};
#endif
