#pragma once

#ifdef FEATURE_ESPNOW

// local includes
#include "displays/bobbymenudisplay.h"

class EspNowSettingsMenu : public BobbyMenuDisplay
{
public:
    EspNowSettingsMenu();

    std::string text() const override;

    void back() override;
};

#endif
