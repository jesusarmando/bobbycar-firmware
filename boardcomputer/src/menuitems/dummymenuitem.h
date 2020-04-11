#pragma once

#include <WString.h>

#include "menuitem.h"

namespace {
class DummyMenuItem : public MenuItemInterface
{
    using Base = MenuItemInterface;

public:
    using Base::Base;

//    DummyMenuItem(const String &title) :
//        m_title{title}
//    {}

    String title() const override { return m_title; }
    void setTitle(const String &title) { m_title = title; }

    void triggered() override {}

private:
    String m_title;
};

template<const char *Ttext>
class StaticDummyMenuItem final : public MenuItem<Ttext>
{
    using Base = MenuItem<Ttext>;

public:
    using Base::Base;

    void triggered() override {}
};
}
