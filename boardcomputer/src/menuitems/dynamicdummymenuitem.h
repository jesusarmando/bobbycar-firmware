#pragma once

#include "menuitems/dummymenuitem.h"
#include "titleinterface.h"

namespace {
class DynamicDummyMenuItem : public DummyMenuItem, public DynamicTitle
{};
}
