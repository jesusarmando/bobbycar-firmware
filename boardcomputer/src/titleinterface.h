#pragma once

#include <WString.h>

namespace {
class TitleInterface {
public:
    virtual String title() const = 0;
};

template<const char *T>
class TitleImpl : public virtual TitleInterface
{
public:
    String title() const override { return T; }
};
}
