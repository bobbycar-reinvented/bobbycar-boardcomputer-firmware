#pragma once

// local includes
#include "menudisplay.h"
#include "texts.h"

class ProfilesMenu :
    public espgui::MenuDisplay,
    public espgui::StaticText<TEXT_PROFILES>
{
public:
    ProfilesMenu();
    void back() override;
};
