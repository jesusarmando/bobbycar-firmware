#pragma once

#include "actioninterface.h"
#include "utils.h"

namespace {
class UpdateSwapFrontBackAction : public virtual ActionInterface
{
public:
    void triggered() override { updateSwapFrontBack(); }
};
}
