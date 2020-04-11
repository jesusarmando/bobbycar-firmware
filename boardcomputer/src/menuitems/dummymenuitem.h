#pragma once

#include "menuitem.h"

namespace {
class DummyMenuItem : public MenuItem
{
public:
    void triggered() final {}
};
}
