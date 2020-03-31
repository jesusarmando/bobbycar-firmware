#pragma once

#include "modebase.h"
#include "globals.h"
#include "utils.h"

#include "../../common.h"

namespace {
class LockscreenMode : public ModeBase
{
public:
    using ModeBase::ModeBase;

    void update() override;

    const char *displayName() const override { return "Lockscreen"; }

private:
    static constexpr int16_t pwm = 0;
    static constexpr ControlType ctrlTyp = ControlType::FieldOrientedControl;
    static constexpr ControlMode ctrlMod = ControlMode::Speed;
};

void LockscreenMode::update()
{
    for (auto &controller : controllers)
    {
        auto &command = controller.command;
        for (MotorState *motor : {&command.left, &command.right})
        {
            motor->ctrlTyp = ctrlTyp;
            motor->ctrlMod = ctrlMod;
            motor->pwm = pwm;
        }
    }

    fixCommonParams();

    sendCommands();
}
}
