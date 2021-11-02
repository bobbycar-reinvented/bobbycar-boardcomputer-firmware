#pragma once

// 3rdparty lib includes
#include <menudisplay.h>
#include <actions/dummyaction.h>
#include <icons/back.h>

// local includes
#include "utils.h"
#include "texts.h"
#include "globals.h"
#include "buildserver.h"

#ifdef FEATURE_OTA
class SelectBuildServerMenu :
    public espgui::MenuDisplay,
    public espgui::StaticText<TEXT_SELECTBUILDSERVERMENU>
{
public:
    SelectBuildServerMenu();

    void back() override;
};
#endif
