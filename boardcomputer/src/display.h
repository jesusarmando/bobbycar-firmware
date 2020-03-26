#pragma once

#include <WString.h>

namespace {
class Display {
public:
    virtual ~Display() = default;

    virtual void start() = 0;
    virtual void update() = 0;

    virtual void rotate(int offset) {}
    virtual void button(bool pressed) {}
};
}
