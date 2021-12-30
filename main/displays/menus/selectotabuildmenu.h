#pragma once

// local includes
#include "displays/bobbymenudisplay.h"

#ifdef FEATURE_OTA

class SelectBuildMenu : public BobbyMenuDisplay
{
    using Base = BobbyMenuDisplay;

public:
    SelectBuildMenu();

    std::string text() const override;

    void update() override;
    void back() override;

private:
    void buildMenuFromJson();
    void buildMenuRequestError(std::string error);
};
#endif
