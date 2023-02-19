#pragma once

// system includes
#include <cstdint>
#include <optional>

// 3rdparty lib includes
#include <espchrono.h>

// local includes
#include "modeinterface.h"
#include "globals.h"
#include "utils.h"
#include "ble_bobby.h"

namespace bobby {

class DefaultMode : public ModeInterface
{
    using Base = ModeInterface;

public:
    void start() override;

    void update() override;

    const char *displayName() const override
    { return "Default"; }

    bool waitForGasLoslass{false};
    bool waitForBremsLoslass{false};

    void setRemoteCommand(const ble::RemoteCommand &command);

private:
    espchrono::millis_clock::time_point m_lastTime{espchrono::millis_clock::now()};
    float m_lastPwm{0};

    std::optional<ble::RemoteCommand> m_remoteCommand;
    espchrono::millis_clock::time_point m_timestamp;
};

namespace modes {
extern DefaultMode defaultMode;
} // namespace modes

} // namespace bobby
