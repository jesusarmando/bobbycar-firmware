#pragma once

#include "menuitem.h"
#include "titleinterface.h"

namespace {
class DynamicDummyMenuItem : public MenuItem, public DynamicTitle
{
public:
    void triggered() final {}
};
}
