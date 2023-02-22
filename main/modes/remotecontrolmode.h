#pragma once

// system includes
#include <cstdint>
#include <optional>

// 3rdparty lib includes
#include <espchrono.h>

// local includes
#include "bobbycar-common.h"
#include "modeinterface.h"
#include "ble_bobby.h"

namespace bobby {

class RemoteControlMode : public ModeInterface
{
    using Base = ModeInterface;

public:
    void update() override;

    const char *displayName() const override
    { return "RemoteControl"; }

    void setRemoteCommand(const ble::RemoteCommand &command);

private:
    std::optional<ble::RemoteCommand> m_remoteCommand;
    espchrono::millis_clock::time_point m_timestamp;
};

namespace modes {
extern RemoteControlMode remoteControlMode;
} // namespace modes

} // namespace bobby
