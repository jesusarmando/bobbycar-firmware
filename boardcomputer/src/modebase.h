#pragma once

#include <WString.h>

namespace {
class ModeBase {
public:
    virtual ~ModeBase() = default;

    virtual void start() {};
    virtual void update() = 0;
    virtual void stop() {};

    virtual const char *displayName() const = 0;

    virtual int framerate() const { return 50; }
};
}
