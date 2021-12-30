#pragma once

// local includes
#include "displays/bobbymenudisplay.h"

#ifdef FEATURE_CLOUD
class CloudSettingsMenu : public BobbyMenuDisplay
{
public:
    CloudSettingsMenu();

    std::string text() const override;

    void back() override;
};
#endif
