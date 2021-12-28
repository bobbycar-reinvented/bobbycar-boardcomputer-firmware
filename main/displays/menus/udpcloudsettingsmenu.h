#pragma once

// local includes
#include "displays/bobbymenudisplay.h"
#include "texts.h"

#ifdef FEATURE_UDPCLOUD
class UdpCloudSettingsMenu :
    public BobbyMenuDisplay,
    public espgui::StaticText<TEXT_UDPCLOUDSETTINGS>
{
public:
    UdpCloudSettingsMenu();

    void back() override;
};
#endif
