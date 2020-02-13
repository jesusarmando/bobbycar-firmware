#pragma once

#include "modebase.h"

namespace {
class ManualMode : public ModeBase
{
public:
    using ModeBase::ModeBase;

    void start() override {};
    void update() override;
    void stop() override {};

    bool manual = true;
    bool enable = true;
    int16_t pwm = 0;
    ControlType ctrlTyp = ControlType::FieldOrientedControl;
    ControlMode ctrlMod = ControlMode::Speed;
};
}
