#pragma once

#ifdef FEATURE_ESPNOW

// 3rdparty lib includes
#include <accessorinterface.h>
#include <actioninterface.h>
#include <espchrono.h>
#include <fmt/core.h>
#include <menudisplay.h>
#include <textinterface.h>
#include <texts.h>

// local includes
#include "displays/bobbymenudisplay.h"
#include "espnowfunctions.h"

using namespace espgui;

namespace espnowsettingsmenu {
} // namespace

class EspNowSettingsMenu :
    public BobbyMenuDisplay,
    public espgui::StaticText<TEXT_ESPNOW_SETTINGS>
{
public:
    EspNowSettingsMenu();
    void back() override;
};

#endif
