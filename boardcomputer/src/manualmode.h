#pragma once

#include <cstdint>

#include "modebase.h"
#include "../../common.h"

namespace {
class ManualMode : public ModeBase
{
public:
    using ModeBase::ModeBase;

    void start() override {};
    void update() override;
    void stop() override {};

    bool potiControl = true;
    int16_t pwm = 0;
    ControlType ctrlTyp = ControlType::FieldOrientedControl;
    ControlMode ctrlMod = ControlMode::Speed;
};
}
