#pragma once

#include "menuitems/dummymenuitem.h"

namespace {
template<typename GETTER>
class LiveStatusMenuItem : public DummyMenuItem
{
public:
    String title() const override { return GETTER::getText(); }
    int color() const override { return TFT_DARKGREY; }
};
}
