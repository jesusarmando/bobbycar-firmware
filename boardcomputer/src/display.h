#pragma once

#include <WString.h>

namespace {
class MenuDisplay;
class ChangeValueDisplayInterface;
}

namespace {
class Display {
public:
    virtual ~Display() = default;

    virtual void start() = 0;
    virtual void update() = 0;
    virtual void redraw() = 0;
    virtual void stop() {}

    virtual void rotate(int offset) {}
    virtual void button() {}

    virtual MenuDisplay *asMenuDisplay() { return nullptr; }
    virtual const MenuDisplay *asMenuDisplay() const { return nullptr; }

    virtual ChangeValueDisplayInterface *asChangeValueDisplayInterface() { return nullptr; }
    virtual const ChangeValueDisplayInterface *asChangeValueDisplayInterface() const { return nullptr; }
};
}
