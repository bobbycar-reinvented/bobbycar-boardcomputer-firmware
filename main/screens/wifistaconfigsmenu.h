#pragma once

// local includes
#include "guihelpers/bobbymenudisplay.h"

namespace bobby {

class WifiStaConfigsMenu : public BobbyMenuDisplay
{
public:
    WifiStaConfigsMenu();

    std::string title() const override;
    void back() override;
};

} // namespace bobby
