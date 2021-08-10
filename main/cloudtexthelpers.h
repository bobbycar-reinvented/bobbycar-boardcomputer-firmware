#pragma once

// 3rdparty lib includes
#include <fmt/core.h>

// local includes
#include "textinterface.h"
#include "cloud.h"

namespace {
#ifdef FEATURE_CLOUD
struct CloudCreatedText : public virtual TextInterface { public: std::string text() const override {
    return fmt::format("created: {}", cloudClient ? "true" : "false"); }};

struct CloudStartedText : public virtual TextInterface {
public:
    std::string text() const override
    {
        std::string text = "started: ";
        if (cloudClient)
            text += cloudStarted ? "true" : "false";
        return text;
    }
};

struct CloudConnectedText : public virtual TextInterface {
public:
    std::string text() const override
    {
        std::string text = "connected: ";
        if (cloudClient)
            text += cloudClient.is_connected() ? "true" : "false";
        return text;
    }
};
#endif
}
