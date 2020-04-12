#pragma once

#include <utility>

#include "menuitem.h"

namespace {
class MenuDefinitionInterface
{
public:
    virtual const std::reference_wrapper<MenuItem> *begin() const = 0;
    virtual const std::reference_wrapper<MenuItem> *end() const = 0;
};
}
