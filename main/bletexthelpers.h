#pragma once

// 3rdparty lib includes
#include <fmt/core.h>

// local includes
#include "textinterface.h"
#include "ble.h"

namespace {
#ifdef FEATURE_BLE
struct BleServerPeerDevicesText : public virtual TextInterface {
public:
    std::string text() const override
    {
        std::string text = "peerDevices: ";
        if (pServer)
            text += std::to_string(pServer->getPeerDevices().size());
        return text;
    }
};

struct BleCharacSubscribedText : public virtual TextInterface {
public:
    std::string text() const override
    {
        std::string text = "subscribed: ";
        if (livestatsCharacteristic)
            text += std::to_string(livestatsCharacteristic->getSubscribedCount());
        return text;
    }
};
#endif
}
