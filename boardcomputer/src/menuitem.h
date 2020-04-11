#pragma once

#include "titleinterface.h"
#include "label.h"

namespace {
class MenuItemInterface : public virtual TitleInterface
{
public:
    virtual void start() {}
    virtual void update() {}
    virtual void stop() {}

    virtual void triggered() = 0;
};

template<const char *T>
class MenuItem : public MenuItemInterface, public TitleImpl<T>
{};
}
