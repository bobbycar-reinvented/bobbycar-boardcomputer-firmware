#pragma once

// 3rdparty lib includes
#include "menuitem.h"

// local includes
#include "guihelpers/menudisplaywithtime.h"
#ifdef MAINMENU_PLUGIN
#include MAINMENU_PLUGIN
#endif

namespace bobby {

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

class MainMenu : public bobby::MenuDisplayWithTime
{
    using Base = bobby::MenuDisplayWithTime;

public:
    MainMenu();

    std::string title() const override;

    void back() override;
};

} // namespace bobby
