#pragma once

// local includes
#include "guihelpers/bobbymenudisplay.h"

namespace bobby {

class UdpCloudSettingsMenu : public BobbyMenuDisplay
{
public:
    UdpCloudSettingsMenu();

    std::string title() const override;

    void back() override;
};
} // namespace bobby
