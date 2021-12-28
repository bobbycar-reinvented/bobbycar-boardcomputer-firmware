#pragma once

// local includes
#include "displays/bobbymenudisplay.h"
#include "texts.h"

#ifdef FEATURE_CLOUD
class CloudSettingsMenu :
    public BobbyMenuDisplay,
    public espgui::StaticText<TEXT_CLOUDSETTINGS>
{
public:
    CloudSettingsMenu();

    void back() override;
};
#endif
