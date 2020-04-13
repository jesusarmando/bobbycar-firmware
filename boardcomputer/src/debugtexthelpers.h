#pragma once

#include "textinterface.h"
#include "globals.h"
#include "utils.h"

namespace {
template<Controller &controller>
struct ControllerTexts
{
    struct BuzzerFreqText : public virtual TextInterface { public: String text() const override { return String{"buzzerFreq: "} + toString(controller.command.buzzer.freq); } };
    struct BuzzerPatternText : public virtual TextInterface { public: String text() const override { return String{"buzzerPattern: "} + toString(controller.command.buzzer.pattern); } };
    struct PoweroffText : public virtual TextInterface { public: String text() const override { return String{"poweroff: "} + toString(controller.command.poweroff); } };
    struct LedText : public virtual TextInterface { public: String text() const override { return String{"led: "} + toString(controller.command.led); } };

    struct LeftCommand
    {
        struct EnableText : public virtual TextInterface { public: String text() const override { return String{"enable: "} + toString(controller.command.left.enable); } };
        struct PwmText : public virtual TextInterface { public: String text() const override { return String{"pwm: "} + toString(controller.command.left.pwm); } };
        struct CtrlTypText : public virtual TextInterface { public: String text() const override { return String{"ctrlTyp: "} + toString(controller.command.left.ctrlTyp); } };
        struct CtrlModText : public virtual TextInterface { public: String text() const override { return String{"ctrlMod: "} + toString(controller.command.left.ctrlMod); } };
        struct IMotMaxText : public virtual TextInterface { public: String text() const override { return String{"iMotMax: "} + toString(controller.command.left.iMotMax); } };
        struct IDcMaxText : public virtual TextInterface { public: String text() const override { return String{"iDcMax: "} + toString(controller.command.left.iDcMax); } };
        struct NMotMaxText : public virtual TextInterface { public: String text() const override { return String{"nMotMax: "} + toString(controller.command.left.nMotMax); } };
        struct FieldWeakMaxText : public virtual TextInterface { public: String text() const override { return String{"fieldWeakMax: "} + toString(controller.command.left.fieldWeakMax); } };
        struct PhaseAdvMaxText : public virtual TextInterface { public: String text() const override { return String{"phaseAdvMax: "} + toString(controller.command.left.phaseAdvMax); } };
    };

    struct RightCommand
    {
        struct EnableText : public virtual TextInterface { public: String text() const override { return String{"enable: "} + toString(controller.command.right.enable); } };
        struct PwmText : public virtual TextInterface { public: String text() const override { return String{"pwm: "} + toString(controller.command.right.pwm); } };
        struct CtrlTypText : public virtual TextInterface { public: String text() const override { return String{"ctrlTyp: "} + toString(controller.command.right.ctrlTyp); } };
        struct CtrlModText : public virtual TextInterface { public: String text() const override { return String{"ctrlMod: "} + toString(controller.command.right.ctrlMod); } };
        struct IMotMaxText : public virtual TextInterface { public: String text() const override { return String{"iMotMax: "} + toString(controller.command.right.iMotMax); } };
        struct IDcMaxText : public virtual TextInterface { public: String text() const override { return String{"iDcMax: "} + toString(controller.command.right.iDcMax); } };
        struct NMotMaxText : public virtual TextInterface { public: String text() const override { return String{"nMotMax: "} + toString(controller.command.right.nMotMax); } };
        struct FieldWeakMaxText : public virtual TextInterface { public: String text() const override { return String{"fieldWeakMax: "} + toString(controller.command.right.fieldWeakMax); } };
        struct PhaseAdvMaxText : public virtual TextInterface { public: String text() const override { return String{"phaseAdvMax: "} + toString(controller.command.right.phaseAdvMax); } };
    };
};

using FrontTexts = ControllerTexts<front>;
using BackTexts = ControllerTexts<back>;
}
