#pragma once

#include "menuitem.h"

namespace {
template<typename GETTER>
class LiveStatusMenuItem : public MenuItem
{
    using Base = MenuItem;

public:
    using Base::Base;

    String title() const override { return GETTER::getText(); }
    void triggered() override {}
    int color() const override { return TFT_DARKGREY; }
};
}
