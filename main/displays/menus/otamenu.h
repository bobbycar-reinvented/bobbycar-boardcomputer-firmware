#pragma once

// local includes
#include "displays/bobbymenudisplay.h"
#include "texts.h"

class OtaMenu :
    public BobbyMenuDisplay,
    public espgui::StaticText<TEXT_UPDATE>
{
public:
    OtaMenu();

    void back() override;
};
