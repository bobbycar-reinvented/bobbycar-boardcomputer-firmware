#pragma once

#include <functional>

#include "bobbycar-protocol/protocol.h"

#include "feedbackparser.h"

class HardwareSerial;

namespace {
struct Controller {
    Controller(HardwareSerial &serial, bool &enableLeft, bool &enableRight, bool &invertLeft, bool &invertRight) :
        serial{serial}, enableLeft{enableLeft}, enableRight{enableRight}, invertLeft{invertLeft}, invertRight{invertRight}
    {
    }
//    Controller(const Controller &) = delete;
//    Controller &operator=(const Controller &) = delete;

    std::reference_wrapper<HardwareSerial> serial;
    bool &enableLeft, &enableRight, &invertLeft, &invertRight;

    Command command{};

    bool feedbackValid{};
    Feedback feedback{};

    FeedbackParser parser{serial, feedbackValid, feedback};
};
}
