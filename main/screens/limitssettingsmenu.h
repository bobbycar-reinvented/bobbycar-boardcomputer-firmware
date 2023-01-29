#pragma once

// local includes
#include "guihelpers/bobbymenudisplay.h"

namespace bobby {

class LimitsSettingsMenu : public BobbyMenuDisplay
{
public:
    LimitsSettingsMenu();

    std::string title() const override;

    void back() override;
};

} // namespace bobby
