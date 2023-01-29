#pragma once

// local includes
#include "guihelpers/bobbymenudisplay.h"

namespace bobby {

class HandbremsSettingsMenu : public BobbyMenuDisplay
{
public:
    HandbremsSettingsMenu();

    std::string title() const override;

    void back() override;
};

} // namespace bobby
