#pragma once

// 3rdparty lib includes
#include "menudisplay.h"
#include "menuitem.h"

// local includes
#include "texts.h"
#ifdef MAINMENU_PLUGIN
#include MAINMENU_PLUGIN
#endif

namespace {
#ifdef MAINMENU_PLUGIN
    GMEN2
#endif
#if !defined(MAINMENU_PLUGIN) and !defined(GMEN3)
#define SHOWITEM !simplified
#else
#define SHOWITEM GMEN3
#endif
} // namespace

class MainMenu :
    public espgui::MenuDisplay,
    public espgui::StaticText<TEXT_MAINMENU>
{
    using Base = espgui::MenuDisplay;
public:
    MainMenu();

    void back() override;
    void start() override;
    void redraw() override;
    espgui::Label m_label_currentTime{145, 6};
};
