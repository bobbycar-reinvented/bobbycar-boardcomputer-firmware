#pragma once

// local includes
#include "bobbycar-common.h"
#include "modeinterface.h"

#ifdef FEATURE_GAMETRAK
class GametrakMode : public ModeInterface
{
    using Base = ModeInterface;

public:
    void start() override;
    void update() override;

    const char *displayName() const override { return "Gametrak"; }

private:
    bool m_flag;
};

namespace modes {
extern GametrakMode gametrakMode;
} // namespace modes
#endif
