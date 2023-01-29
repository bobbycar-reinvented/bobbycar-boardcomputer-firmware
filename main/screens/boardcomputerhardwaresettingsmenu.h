#pragma once

// local includes
#include "guihelpers/bobbymenudisplay.h"

namespace bobby {

class BoardcomputerHardwareSettingsMenu : public BobbyMenuDisplay
{
public:
    BoardcomputerHardwareSettingsMenu();

    std::string title() const override;

    void back() override;
};

} // namespace bobby
