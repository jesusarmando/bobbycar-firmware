#pragma once

#include <TFT_eSPI.h>

#include "titleinterface.h"

namespace {
class MenuItem : public virtual TitleInterface
{
public:
    virtual void start() {}
    virtual void update() {}
    virtual void stop() {}

    virtual void triggered() = 0;

    virtual int color() const { return TFT_WHITE; }
};
}
