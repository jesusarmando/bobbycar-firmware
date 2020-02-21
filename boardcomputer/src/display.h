#pragma once

namespace {
class Display {
public:
    virtual void start() = 0;
    virtual void update() = 0;
    virtual void stop() = 0;
    virtual int framerate() const = 0;
};
}