#pragma once

// local includes
#include "guihelpers/bobbymenudisplay.h"

namespace bobby {

class TempomatModeSettingsMenu : public BobbyMenuDisplay
{
public:
    TempomatModeSettingsMenu();

    std::string title() const override;

    void back() override;
};
} // namespace bobby
