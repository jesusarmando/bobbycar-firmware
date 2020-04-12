#pragma once

#include "icon.h"

namespace {
template<uint16_t width, uint16_t height>
class IconInterface
{
public:
    virtual const Icon<width, height> *icon() const { return nullptr; }
};

template<uint16_t width, uint16_t height, const Icon<width, height> *T>
class StaticIcon : public virtual IconInterface<24, 24>
{
public:
    virtual const Icon<width, height> *icon() const { return T; }
};
}
