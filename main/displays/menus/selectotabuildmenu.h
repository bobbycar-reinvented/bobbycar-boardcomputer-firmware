#pragma once

// local includes
#include "displays/bobbymenudisplay.h"
#include "texts.h"

#ifdef FEATURE_OTA

class SelectBuildMenu :
    public BobbyMenuDisplay,
    public espgui::StaticText<TEXT_SELECTBUILD>
{
    using Base = BobbyMenuDisplay;

public:
    SelectBuildMenu();
    void update() override;
    void back() override;

private:
    void buildMenuFromJson();
    void buildMenuRequestError(std::string error);
};
#endif
