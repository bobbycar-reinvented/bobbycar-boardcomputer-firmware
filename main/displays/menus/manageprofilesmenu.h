#pragma once

// local includes
#include <displays/bobbymenudisplay.h>

class ManageProfilesMenu : public BobbyMenuDisplay
{
public:
    ManageProfilesMenu();

    std::string text() const override;

    void back() override;
};
