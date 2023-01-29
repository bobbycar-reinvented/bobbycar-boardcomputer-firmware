#pragma once

// local includes
#include "guihelpers/bobbymenudisplay.h"

namespace bobby {

class WifiApSettingsMenu : public BobbyMenuDisplay
{
public:
    WifiApSettingsMenu();

    std::string title() const override;
    void back() override;
};
} // namespace bobby
