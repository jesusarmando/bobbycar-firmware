#pragma once

#include "actioninterface.h"

#include "settings.h"

namespace {
template<typename T, T &target, const T *source>
class CopyValueAction : public virtual ActionInterface
{
public:
    void triggered() override { target = *source; }
};
}
