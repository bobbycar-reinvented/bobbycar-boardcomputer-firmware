#pragma once

// local includes
#include "displays/bobbymenudisplay.h"
#include "texts.h"

#ifdef FEATURE_OTA

class SelectBuildserverBranchMenu :
    public BobbyMenuDisplay,
    public espgui::StaticText<TEXT_SELECT_BRANCH>
{
    using Base = espgui::MenuDisplay;
public:
    SelectBuildserverBranchMenu();

    void buildMenuRequestError(std::string error);
    void update() override;
    void back() override;
};

#endif
