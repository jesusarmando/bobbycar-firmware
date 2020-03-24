#pragma once

#include <array>

#include "changevaluedisplay.h"
#include "menudisplay.h"
#include "menuitems/setvaluemenuitem.h"
#include "menuitems/switchscreenmenuitem.h"

namespace {
template<>
class ChangeValueDisplay<ControlType> final : public MenuDisplay
{
public:
    ChangeValueDisplay(const char *title, ControlType &value, Display &prevDisplay) :
        m_title{title},
        m_value{value},
        item0{ControlType::Commutation, value, prevDisplay, "Commutation"},
        item1{ControlType::Sinusoidal, value, prevDisplay, "Sinusoidal"},
        item2{ControlType::FieldOrientedControl, value, prevDisplay, "Field oriented control"},
        item3{prevDisplay, "Back"}
    {
    }

    void start() override
    {
        MenuDisplay::start();

        if (m_value == ControlType::Commutation)
            m_current = begin() + 0;
        else if (m_value == ControlType::Sinusoidal)
            m_current = begin() + 1;
        else if (m_value == ControlType::FieldOrientedControl)
            m_current = begin() + 2;
        else
            m_current = begin() + 3;
    }

    const char *title() const override { return m_title; }

    const std::reference_wrapper<const MenuItem> *begin() const override { return std::begin(carr); };
    const std::reference_wrapper<const MenuItem> *end() const override { return std::end(carr); };

private:
    const char * const m_title;

    ControlType &m_value;

    SetValueMenuItem<ControlType> item0;
    SetValueMenuItem<ControlType> item1;
    SetValueMenuItem<ControlType> item2;
    SwitchScreenItem item3;

    const std::array<std::reference_wrapper<const MenuItem>, 4> carr{{
        std::cref<MenuItem>(item0),
        std::cref<MenuItem>(item1),
        std::cref<MenuItem>(item2),
        std::cref<MenuItem>(item3)
    }};
};
}
