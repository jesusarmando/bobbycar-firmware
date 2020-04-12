#pragma once

#include "actions/actioninterface.h"
#include "utils.h"

namespace {
template<typename Tscreen>
class SwitchScreenAction : public virtual ActionInterface
{
public:
    void triggered() override { switchScreen<Tscreen>(); }
};
}
