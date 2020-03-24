#pragma once

#include <array>

#include "changevaluedisplay.h"
#include "menudisplay.h"
#include "menuitems/setvaluemenuitem.h"
#include "menuitems/switchscreenmenuitem.h"

namespace {
template<>
class ChangeValueDisplay<bool> final : public MenuDisplay
{
public:
    ChangeValueDisplay(const char *title, bool &value, Display &prevDisplay) :
        m_title{title},
        m_value{value},
        item0{true, value, prevDisplay, "true"},
        item1{false, value, prevDisplay, "false"},
        item2{prevDisplay, "Back"}
    {
    }

    void start() override
    {
        MenuDisplay::start();

        if (m_value == true)
            m_current = begin() + 0;
        else if (m_value == false)
            m_current = begin() + 1;
    }

    const char *title() const override { return m_title; }

    const std::reference_wrapper<const MenuItem> *begin() const override { return std::begin(carr); };
    const std::reference_wrapper<const MenuItem> *end() const override { return std::end(carr); };

private:
    const char * const m_title;

    bool &m_value;

    SetValueMenuItem<bool> item0;
    SetValueMenuItem<bool> item1;
    SwitchScreenItem item2;

    const std::array<std::reference_wrapper<const MenuItem>, 3> carr{{
        std::cref<MenuItem>(item0),
        std::cref<MenuItem>(item1),
        std::cref<MenuItem>(item2)
    }};
};
}
