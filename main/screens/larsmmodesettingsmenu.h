#pragma once

// local includes
#include "guihelpers/bobbymenudisplay.h"

namespace bobby {

class LarsmModeSettingsMenu : public BobbyMenuDisplay
{
public:
    LarsmModeSettingsMenu();

    std::string title() const override;

    void back() override;
};

} // namespace bobby
