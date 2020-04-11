#pragma once

#include "modebase.h"

namespace {
class LarsmMode final : public ModeBase
{
public:
    using ModeBase::ModeBase;

    void update() override {};

    const char *displayName() const override { return "Larsmm"; }
};

namespace modes {
LarsmMode larsmMode;
}
}
