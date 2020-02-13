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

    int16_t frontPercentage{100}, backPercentage{100};
    bool waitForGasLoslass{false};
    bool waitForBremsLoslass{false};
};
}
