#pragma once

#include "menuitem.h"

namespace {
template<const char *Ttext>
class DummyMenuItem final : public MenuItem<Ttext>
{
public:
    void triggered() const override {}
};
}
