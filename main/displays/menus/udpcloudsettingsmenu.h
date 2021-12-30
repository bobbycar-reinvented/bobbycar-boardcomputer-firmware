#pragma once

// local includes
#include "displays/bobbymenudisplay.h"

#ifdef FEATURE_UDPCLOUD
class UdpCloudSettingsMenu : public BobbyMenuDisplay
{
public:
    UdpCloudSettingsMenu();

    std::string text() const override;

    void back() override;
};
#endif
