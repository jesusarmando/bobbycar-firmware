#pragma once

namespace {
class TitleInterface {
public:
    virtual const char *title() const = 0;
};

template<const char *T>
class TitleImpl : public virtual TitleInterface
{
public:
    const char *title() const override { return T; }
};
}
