#pragma once

// 3rdparty lib includes

// local includes
#include "displays/bobbymenudisplay.h"
#include "texts.h"

#ifdef FEATURE_OTA

class SelectBuildServerMenu :
    public BobbyMenuDisplay,
    public espgui::StaticText<TEXT_SELECTBUILDSERVERMENU>
{
public:
    SelectBuildServerMenu();

    void back() override;
};
#endif
