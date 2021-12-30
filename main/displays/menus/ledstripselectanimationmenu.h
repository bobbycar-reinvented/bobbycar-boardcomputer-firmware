#pragma once

// Local includes
#include "displays/bobbymenudisplay.h"

#ifdef FEATURE_LEDSTRIP
class LedstripSelectAnimationMenu : public BobbyMenuDisplay
{
public:
    LedstripSelectAnimationMenu();

    std::string text() const override;

    void back() override;
};
#endif
