#pragma once

#include "titleinterface.h"

namespace {
class MenuItemInterface : public virtual TitleInterface
{
public:
    virtual void triggered() const = 0;
};

template<const char *T>
class MenuItem : public MenuItemInterface, public TitleImpl<T>
{};
}
