#pragma once

#include <WString.h>

namespace {
class Display {
public:
    virtual ~Display() = default;

    virtual void start() {};
    virtual void update() {};
    virtual void redraw() = 0;
    virtual int framerate() const = 0;

    virtual void rotate(int offset) {}
    virtual void button(bool pressed) {}
};
}
