#pragma once

// 3rdparty lib includes

// local includes
#include "displays/bobbymenudisplay.h"

#ifdef FEATURE_OTA

class SelectBuildServerMenu : public BobbyMenuDisplay
{
public:
    SelectBuildServerMenu();

    std::string text() const override;

    void back() override;
};
#endif
