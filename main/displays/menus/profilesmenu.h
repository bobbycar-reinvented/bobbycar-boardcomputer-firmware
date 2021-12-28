#pragma once

// local includes
#include "displays/bobbymenudisplay.h"
#include "texts.h"

class ProfilesMenu :
    public BobbyMenuDisplay,
    public espgui::StaticText<TEXT_PROFILES>
{
public:
    ProfilesMenu();
    void back() override;
};
