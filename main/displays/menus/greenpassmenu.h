#pragma once


// 3rdparty lib includes
#include <accessorinterface.h>
#include <qrcode.h>

// local includes
#include "displays/bobbymenudisplay.h"
#include "texts.h"

class GreenPassMenu :
    public BobbyMenuDisplay,
    public espgui::StaticText<TEXT_GREENPASS>
{
public:
    GreenPassMenu();
    void back() override;
};
