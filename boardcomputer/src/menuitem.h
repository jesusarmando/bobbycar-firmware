#pragma once

namespace {
class MenuItemInterface
{
public:
    virtual void triggered() const = 0;
    virtual const char *text() const = 0;
};

template<const char *T>
class MenuItem : public MenuItemInterface
{
public:
    const char *text() const override { return T; }
};
}
