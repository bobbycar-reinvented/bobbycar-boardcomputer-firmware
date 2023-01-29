#pragma once

// local includes
#include "guihelpers/bobbymenudisplay.h"

namespace bobby {

class MotortestModeSettingsMenu : public BobbyMenuDisplay
{
public:
    MotortestModeSettingsMenu();

    std::string title() const override;

    void back() override;
};
} // namespace bobby
