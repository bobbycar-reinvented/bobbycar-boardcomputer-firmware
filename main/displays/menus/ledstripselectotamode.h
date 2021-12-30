#pragma once

// local includes
#include "displays/bobbymenudisplay.h"

#if defined(FEATURE_LEDSTRIP) && defined(FEATURE_OTA)
class LedstripOtaAnimationChangeMenu : public BobbyMenuDisplay
{
public:
    LedstripOtaAnimationChangeMenu();

    std::string text() const override;
    void back() override;
};
#endif
