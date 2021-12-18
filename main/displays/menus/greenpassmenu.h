#pragma once

#include <qrcode.h>

// local includes
#include "menudisplay.h"
#include "texts.h"

class GreenPassMenu :
    public espgui::MenuDisplay,
    public espgui::StaticText<TEXT_GREENPASS>
{
    using Base = espgui::MenuDisplay;
public:
    GreenPassMenu();
    void back() override;
};
