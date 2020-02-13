#pragma once

#include "modebase.h"

namespace {
class BluetoothMode : public ModeBase
{
public:
    using ModeBase::ModeBase;

    void start() override;
    void update() override;
    void stop() override {};
};
}
