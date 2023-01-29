#pragma once

// local includes
#include "guihelpers/bobbymenudisplay.h"

namespace bobby {

class MickModeSettingsMenu : public BobbyMenuDisplay
{
public:
    MickModeSettingsMenu();

    std::string title() const override;

    void back() override;
};
} // namespace bobby
