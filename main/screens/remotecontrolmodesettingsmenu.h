#pragma once

// local includes
#include "guihelpers/bobbymenudisplay.h"

namespace bobby {

class RemoteControlModeSettingsMenu : public BobbyMenuDisplay
{
public:
    RemoteControlModeSettingsMenu();

    std::string title() const override;

    void back() override;
};

} // namespace bobby
