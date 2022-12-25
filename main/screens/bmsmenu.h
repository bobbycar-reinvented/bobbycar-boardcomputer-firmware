#pragma once

#if defined(FEATURE_BLUETOOTH) && defined(FEATURE_BMS)
// local includes
#include "guihelpers/bobbymenudisplay.h"

class BmsMenu : public BobbyMenuDisplay
{
public:
    BmsMenu();

    std::string text() const override { return TEXT_BMS; }
    void back() override;
};
#endif
