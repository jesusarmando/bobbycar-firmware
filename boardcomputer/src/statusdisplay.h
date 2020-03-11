#pragma once

#include "display.h"

namespace {
class StatusDisplay : public Display
{
public:
    void start() override;
    void update() override;
    void stop() override;

    int framerate() const override { return m_framerate; }
    void setFramerate(int framerate) { m_framerate = framerate; }

private:
    int m_framerate{2};
};
}
