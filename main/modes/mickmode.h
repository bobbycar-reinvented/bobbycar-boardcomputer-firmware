#pragma once

// 3rdparty lib includes
#include <bobbycar-common.h>
#include <espchrono.h>

// local includes
#include "modeinterface.h"

namespace bobby {

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

} // namespace bobby
