#pragma once

#include "icon.h"

namespace {
template<uint16_t width, uint16_t height>
class IconInterface
{
public:
    virtual const Icon<width, height> *icon() const { return nullptr; }
};
}
