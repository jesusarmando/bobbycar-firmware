#pragma once

#include "display.h"

namespace {
class StatusDisplay : public Display
{
public:
    void start() override;
    void update() override;
    void stop() override {};
    int framerate() const override { return 5; }
};
}
