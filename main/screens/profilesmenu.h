#pragma once

// local includes
#include "guihelpers/bobbymenudisplay.h"

namespace bobby {

class ProfilesMenu : public BobbyMenuDisplay
{
public:
    ProfilesMenu();

    std::string title() const override;

    void back() override;
};
} // namespace bobby
