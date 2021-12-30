#pragma once

// local includes
#include "bobbymenudisplay.h"

class CalibrateVoltageDisplay : public BobbyMenuDisplay
{
public:
    CalibrateVoltageDisplay();

    std::string text() const override;

    void back() override;
};
