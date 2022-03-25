#pragma once

// 3rdparty lib includes
#include <espchrono.h>

// local includes
#include "bobbycar-common.h"
#include "modeinterface.h"

class MickMode : public ModeInterface
{
    using Base = ModeInterface;

public:
    void start() override;
    void update() override;

    const char *displayName() const override { return "mick"; }

private:
    float pwm_;
    espchrono::millis_clock::time_point lastUpdate_{espchrono::millis_clock::now()};
};

namespace modes {
extern MickMode mickMode;
} // namespace modes
