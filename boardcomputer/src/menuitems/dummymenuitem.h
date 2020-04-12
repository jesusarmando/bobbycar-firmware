#pragma once

#include "menuitems/menuitem.h"

namespace {
class DummyMenuItem : public MenuItem
{
public:
    void triggered() final {}
};
}
