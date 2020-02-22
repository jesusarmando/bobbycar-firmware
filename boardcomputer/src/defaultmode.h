#pragma once

#include <cstdint>

#include <Arduino.h>

#include "modebase.h"
#include "../../common.h"

namespace {
class DefaultMode : public ModeBase
{
public:
    using ModeBase::ModeBase;

    void start() override {};
    void update() override;
    void stop() override {};

    ControlType ctrlTyp = ControlType::FieldOrientedControl;
    ControlMode ctrlMod = ControlMode::Torque;
    bool enableWeakeningSmoothening{true};
    int16_t weakeningSmoothening{2};
    unsigned long lastTime{millis()};
    float lastPwm{0};
    int16_t frontPercentage{100}, backPercentage{100};
    bool waitForGasLoslass{false};
    bool waitForBremsLoslass{false};
};
}
