#pragma once

#include <utility>

#include "menuitem.h"

namespace {
class MenuDefinitionInterface
{
public:
    virtual void runForEveryMenuItem(std::function<void(MenuItem&)> &&callback) = 0;
};
}
