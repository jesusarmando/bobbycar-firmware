#pragma once

#include <WString.h>

namespace {
class Display {
public:
    virtual ~Display() = default;

    virtual void start() = 0;
    virtual void redraw() = 0;
    virtual void stop() = 0;
    virtual int framerate() const = 0;

    virtual const char *displayName() const = 0;

    virtual void rotate(int offset) {}
    virtual void button(bool pressed) {}
};
}
