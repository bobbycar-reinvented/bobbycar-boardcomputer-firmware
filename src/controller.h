#pragma once

#include <functional>

#include "bobbycar-protocol/bobbycar-common.h"
#include "bobbycar-protocol/bobbycar-serial.h"

#include "types.h"

#ifndef FEATURE_CAN
#include "feedbackparser.h"
#endif

#ifndef FEATURE_CAN
class HardwareSerial;
#endif

namespace {
struct Controller {
    Controller(
#ifndef FEATURE_CAN
        HardwareSerial &serial,
#endif
        bool &enableLeft, bool &enableRight, bool &invertLeft, bool &invertRight) :
#ifndef FEATURE_CAN
        serial{serial},
#endif
        enableLeft{enableLeft}, enableRight{enableRight}, invertLeft{invertLeft}, invertRight{invertRight}
    {
    }
//    Controller(const Controller &) = delete;
//    Controller &operator=(const Controller &) = delete;

#ifndef FEATURE_CAN
    std::reference_wrapper<HardwareSerial> serial;
#endif
    bool &enableLeft, &enableRight, &invertLeft, &invertRight;

    Command command{};

#ifdef FEATURE_CAN
    millis_t lastCanFeedback{};
#endif
    bool feedbackValid{};
    Feedback feedback{};

#ifndef FEATURE_CAN
    FeedbackParser parser{serial, feedbackValid, feedback};
#endif
};
}
