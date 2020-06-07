#pragma once

#include "textinterface.h"
#include "globals.h"
#include "utils.h"

namespace {
template<typename controller>
struct ControllerTexts
{
    ControllerTexts() = delete;
    ~ControllerTexts() = delete;

    struct BuzzerFreqText : public virtual TextInterface { public: String text() const override { return String{"buzzerFreq: "} + toString(controller::get().command.buzzer.freq); } };
    struct BuzzerPatternText : public virtual TextInterface { public: String text() const override { return String{"buzzerPattern: "} + toString(controller::get().command.buzzer.pattern); } };
    struct PoweroffText : public virtual TextInterface { public: String text() const override { return String{"poweroff: "} + toString(controller::get().command.poweroff); } };
    struct LedText : public virtual TextInterface { public: String text() const override { return String{"led: "} + toString(controller::get().command.led); } };

    struct LeftCommand
    {
        LeftCommand() = delete;
        ~LeftCommand() = delete;

        struct EnableText : public virtual TextInterface { public: String text() const override { return String{"enable: "} + toString(controller::get().command.left.enable); } };
        struct PwmText : public virtual TextInterface { public: String text() const override { return String{"pwm: "} + toString(controller::get().command.left.pwm); } };
        struct CtrlTypText : public virtual TextInterface { public: String text() const override { return String{"ctrlTyp: "} + toString(controller::get().command.left.ctrlTyp); } };
        struct CtrlModText : public virtual TextInterface { public: String text() const override { return String{"ctrlMod: "} + toString(controller::get().command.left.ctrlMod); } };
        struct IMotMaxText : public virtual TextInterface { public: String text() const override { return String{"iMotMax: "} + toString(controller::get().command.left.iMotMax); } };
        struct IDcMaxText : public virtual TextInterface { public: String text() const override { return String{"iDcMax: "} + toString(controller::get().command.left.iDcMax); } };
        struct NMotMaxText : public virtual TextInterface { public: String text() const override { return String{"nMotMax: "} + toString(controller::get().command.left.nMotMax); } };
        struct FieldWeakMaxText : public virtual TextInterface { public: String text() const override { return String{"fieldWeakMax: "} + toString(controller::get().command.left.fieldWeakMax); } };
        struct PhaseAdvMaxText : public virtual TextInterface { public: String text() const override { return String{"phaseAdvMax: "} + toString(controller::get().command.left.phaseAdvMax); } };
    };

    struct RightCommand
    {
        RightCommand() = delete;
        ~RightCommand() = delete;

        struct EnableText : public virtual TextInterface { public: String text() const override { return String{"enable: "} + toString(controller::get().command.right.enable); } };
        struct PwmText : public virtual TextInterface { public: String text() const override { return String{"pwm: "} + toString(controller::get().command.right.pwm); } };
        struct CtrlTypText : public virtual TextInterface { public: String text() const override { return String{"ctrlTyp: "} + toString(controller::get().command.right.ctrlTyp); } };
        struct CtrlModText : public virtual TextInterface { public: String text() const override { return String{"ctrlMod: "} + toString(controller::get().command.right.ctrlMod); } };
        struct IMotMaxText : public virtual TextInterface { public: String text() const override { return String{"iMotMax: "} + toString(controller::get().command.right.iMotMax); } };
        struct IDcMaxText : public virtual TextInterface { public: String text() const override { return String{"iDcMax: "} + toString(controller::get().command.right.iDcMax); } };
        struct NMotMaxText : public virtual TextInterface { public: String text() const override { return String{"nMotMax: "} + toString(controller::get().command.right.nMotMax); } };
        struct FieldWeakMaxText : public virtual TextInterface { public: String text() const override { return String{"fieldWeakMax: "} + toString(controller::get().command.right.fieldWeakMax); } };
        struct PhaseAdvMaxText : public virtual TextInterface { public: String text() const override { return String{"phaseAdvMax: "} + toString(controller::get().command.right.phaseAdvMax); } };
    };

    struct BatVoltageText : public virtual TextInterface { public: String text() const override { auto line = String{"batVoltage: "}; if (controller::get().feedbackValid) line += toString(controller::get().feedback.batVoltage); return line; } };
    struct BatVoltageFixedText : public virtual TextInterface { public: String text() const override { auto line = String{"batVoltage: "}; if (controller::get().feedbackValid) line += toString(fixBatVoltage(controller::get().feedback.batVoltage)) + 'V'; return line; } };
    struct BoardTempText : public virtual TextInterface { public: String text() const override { auto line = String{"boardTemp: "}; if (controller::get().feedbackValid) line += toString(controller::get().feedback.boardTemp); return line; } };
    struct BoardTempFixedText : public virtual TextInterface { public: String text() const override { auto line = String{"boardTemp: "}; if (controller::get().feedbackValid) line += toString(fixBoardTemp(controller::get().feedback.boardTemp)) + 'C'; return line; } };
    struct TimeoutCntSerialText : public virtual TextInterface { public: String text() const override { auto line = String{"timeoutCntSerial: "}; if (controller::get().feedbackValid) line += toString(controller::get().feedback.timeoutCntSerial); return line; } };

    struct LeftFeedback
    {
        LeftFeedback() = delete;
        ~LeftFeedback() = delete;

        struct AngleText : public virtual TextInterface { public: String text() const override { auto line = String{"angle: "}; if (controller::get().feedbackValid) line += toString(controller::get().feedback.left.angle); return line; } };
        struct SpeedText : public virtual TextInterface { public: String text() const override { auto line = String{"speed: "}; if (controller::get().feedbackValid) line += toString(controller::get().feedback.left.speed); return line; } };
        struct SpeedKmhText : public virtual TextInterface { public: String text() const override { auto line = String{"speed kmh: "}; if (controller::get().feedbackValid) line += toString(convertToKmh(controller::get().feedback.left.speed)); return line; } };
        struct ErrorText : public virtual TextInterface { public: String text() const override { auto line = String{"error: "}; if (controller::get().feedbackValid) line += toString(controller::get().feedback.left.error); return line; } };
        struct CurrentText : public virtual TextInterface { public: String text() const override { auto line = String{"current: "}; if (controller::get().feedbackValid) line += toString(controller::get().feedback.left.current); return line; } };
        struct CurrentFixedText : public virtual TextInterface { public: String text() const override { auto line = String{"current: "}; if (controller::get().feedbackValid) line += toString(fixCurrent(controller::get().feedback.left.current)) + 'A'; return line; } };
        struct ChopsText : public virtual TextInterface { public: String text() const override { auto line = String{"chops: "}; if (controller::get().feedbackValid) line += toString(controller::get().feedback.left.chops); return line; } };
        struct HallText : public virtual TextInterface { public: String text() const override { auto line = String{"hall: "}; if (controller::get().feedbackValid) line += hallString(controller::get().feedback.left); return line; } };
    };

    struct RightFeedback
    {
        RightFeedback() = delete;
        ~RightFeedback() = delete;

        struct AngleText : public virtual TextInterface { public: String text() const override { auto line = String{"angle: "}; if (controller::get().feedbackValid) line += toString(controller::get().feedback.right.angle); return line; } };
        struct SpeedText : public virtual TextInterface { public: String text() const override { auto line = String{"speed: "}; if (controller::get().feedbackValid) line += toString(controller::get().feedback.right.speed); return line; } };
        struct SpeedKmhText : public virtual TextInterface { public: String text() const override { auto line = String{"speed kmh: "}; if (controller::get().feedbackValid) line += toString(convertToKmh(controller::get().feedback.right.speed)); return line; } };
        struct ErrorText : public virtual TextInterface { public: String text() const override { auto line = String{"error: "}; if (controller::get().feedbackValid) line += toString(controller::get().feedback.right.error); return line; } };
        struct CurrentText : public virtual TextInterface { public: String text() const override { auto line = String{"current: "}; if (controller::get().feedbackValid) line += toString(controller::get().feedback.right.current); return line; } };
        struct CurrentFixedText : public virtual TextInterface { public: String text() const override { auto line = String{"current: "}; if (controller::get().feedbackValid) line += toString(fixCurrent(controller::get().feedback.right.current)) + 'A'; return line; } };
        struct ChopsText : public virtual TextInterface { public: String text() const override { auto line = String{"chops: "}; if (controller::get().feedbackValid) line += toString(controller::get().feedback.right.chops); return line; } };
        struct HallText : public virtual TextInterface { public: String text() const override { auto line = String{"hall: "}; if (controller::get().feedbackValid) line += hallString(controller::get().feedback.right); return line; } };
    };
};

using FrontTexts = ControllerTexts<FrontControllerGetter>;
using BackTexts = ControllerTexts<BackControllerGetter>;
}
