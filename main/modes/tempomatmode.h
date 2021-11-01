#pragma once

// system includes
#include <cstdint>

// local includes
#include "bobbycar-common.h"
#include "modeinterface.h"

class TempomatMode : public ModeInterface
{
    using Base = ModeInterface;

public:
    void start() override;
    void update() override;

    const char *displayName() const override { return "Tempomat"; }

    int16_t nCruiseMotTgt;
};

namespace modes {
extern TempomatMode tempomatMode;
} // namespace modes
