#pragma once

// local includes
#include "displays/bobbymenudisplay.h"

class ProfilesMenu : public BobbyMenuDisplay
{
public:
    ProfilesMenu();

    std::string text() const override;

    void back() override;
};
