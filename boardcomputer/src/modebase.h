#pragma once

#include <WString.h>

namespace {
class ModeBase {
public:
    virtual void start() = 0;
    virtual void update() = 0;
    virtual void stop() = 0;

    virtual const char *displayName() const = 0;
};
}
