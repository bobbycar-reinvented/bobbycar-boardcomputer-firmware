#pragma once

// local includes
#include "guihelpers/bobbymenudisplay.h"

namespace bobby {

class CloudSettingsMenu : public BobbyMenuDisplay
{
public:
    CloudSettingsMenu();

    std::string title() const override;

    void back() override;
};

} // namespace bobby
