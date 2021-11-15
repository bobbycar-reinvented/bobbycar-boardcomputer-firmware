#pragma once

// 3rdparty lib includes
#include <menudisplay.h>
#include <menuitem.h>
#include <icons/back.h>
#include <actions/dummyaction.h>
#include <actions/switchscreenaction.h>

// Local includes
#include "utils.h"
#include "texts.h"

class StatisticsMenu :
    public espgui::MenuDisplay,
    public espgui::StaticText<TEXT_STATISTICSMENU>
{
public:
    StatisticsMenu();

    void back() override;
};
