#pragma once

#include <stdint.h>

#include "modebase.h"

namespace {
class DefaultMode : public ModeBase
{
public:
    using ModeBase::ModeBase;

    void start() override {};
    void update() override;
    void stop() override {};

    bool enableWeakeningSmoothening{true};
    int16_t weakeningSmoothening{1};
    float lastPwm{0};
    int16_t frontPercentage{100}, backPercentage{100};
    bool waitForGasLoslass{false};
    bool waitForBremsLoslass{false};
};
}
