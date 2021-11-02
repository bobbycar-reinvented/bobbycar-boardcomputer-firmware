#pragma once

// local includes
#include "menudisplay.h"
#include "texts.h"

class GraphsMenu :
    public espgui::MenuDisplay,
    public espgui::StaticText<TEXT_GRAPHS>
{
public:
    GraphsMenu();

    void back() override;
};
