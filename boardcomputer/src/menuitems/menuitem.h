#pragma once

#include <TFT_eSPI.h>

#include "titleinterface.h"
#include "actions/actioninterface.h"

namespace {
class MenuItem : public virtual ActionInterface, public virtual TitleInterface
{
public:
    virtual void start() {}
    virtual void update() {}
    virtual void stop() {}

    virtual int font() const { return 4; }
    virtual int color() const { return TFT_WHITE; }
};
}
