#pragma once

#include "menuitem.h"
#include "titleinterface.h"

namespace {
template<const char *Ttext>
class StaticDummyMenuItem final : public MenuItem, public StaticTitle<Ttext>
{
public:
    void triggered() override {}
};
}
