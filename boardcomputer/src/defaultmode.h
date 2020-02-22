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
    int16_t weakeningSmoothening{20};
    unsigned long lastTime{millis()};
    float lastPwm{0};
    int16_t frontPercentage{100}, backPercentage{100};
    bool waitForGasLoslass{false};
    bool waitForBremsLoslass{false};

    int16_t add_schwelle = 950;
    int16_t gas1_wert = 1000;
    int16_t gas2_wert = 1000;
    int16_t brems1_wert = 500;
    int16_t brems2_wert = 750;
};
}
