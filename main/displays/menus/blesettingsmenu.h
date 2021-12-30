#pragma once

// local includes
#include "displays/bobbymenudisplay.h"

#ifdef FEATURE_BLE

class BleSettingsMenu : public BobbyMenuDisplay
{
public:
    BleSettingsMenu();

    std::string text() const override;

    void back() override;
};
#endif
