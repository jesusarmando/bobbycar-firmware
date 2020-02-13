#pragma once

namespace {
class ModeBase {
public:
    virtual void start() = 0;
    virtual void update() = 0;
    virtual void stop() = 0;
};
}
