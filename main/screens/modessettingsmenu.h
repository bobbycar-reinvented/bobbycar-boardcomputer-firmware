#pragma once

// local includes
#include "guihelpers/bobbymenudisplay.h"

namespace bobby {

class ModesSettingsMenu : public BobbyMenuDisplay
{
public:
    ModesSettingsMenu();

    std::string title() const override;

    void back() override;
};

} // namespace bobby
