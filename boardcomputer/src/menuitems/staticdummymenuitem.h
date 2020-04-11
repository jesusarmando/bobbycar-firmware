#pragma once

#include "menuitems/dummymenuitem.h"
#include "titleinterface.h"

namespace {
template<const char *Ttext>
class StaticDummyMenuItem final : public DummyMenuItem, public StaticTitle<Ttext>
{};
}
