#pragma once

// local includes
#include "guihelpers/bobbymenudisplay.h"

namespace bobby {

class BleSettingsMenu : public BobbyMenuDisplay
{
public:
    BleSettingsMenu();

    std::string title() const override;

    void back() override;
};

} // namespace bobby
