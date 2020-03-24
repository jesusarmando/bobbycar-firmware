#pragma once

#include <array>

#include "changevaluedisplay.h"
#include "menudisplay.h"
#include "menuitems/setvaluemenuitem.h"
#include "menuitems/switchscreenmenuitem.h"

namespace {
template<>
class ChangeValueDisplay<ControlMode> final : public MenuDisplay
{
public:
    ChangeValueDisplay(const char *title, ControlMode &value, Display &prevDisplay) :
        m_title{title},
        m_value{value},
        item0{ControlMode::OpenMode, value, prevDisplay, "Open mode"},
        item1{ControlMode::Voltage, value, prevDisplay, "Voltage"},
        item2{ControlMode::Speed, value, prevDisplay, "Speed"},
        item3{ControlMode::Torque, value, prevDisplay, "Torque"},
        item4{prevDisplay, "Back"}
    {
    }

    void start() override
    {
        MenuDisplay::start();

        if (m_value == ControlMode::OpenMode)
            m_current = begin() + 0;
        else if (m_value == ControlMode::Voltage)
            m_current = begin() + 1;
        else if (m_value == ControlMode::Speed)
            m_current = begin() + 2;
        else if (m_value == ControlMode::Torque)
            m_current = begin() + 3;
        else
            m_current = begin() + 4;
    }

    const char *title() const override { return m_title; }

    const std::reference_wrapper<const MenuItem> *begin() const override { return std::begin(carr); };
    const std::reference_wrapper<const MenuItem> *end() const override { return std::end(carr); };

private:
    const char * const m_title;

    ControlMode &m_value;

    SetValueMenuItem<ControlMode> item0;
    SetValueMenuItem<ControlMode> item1;
    SetValueMenuItem<ControlMode> item2;
    SetValueMenuItem<ControlMode> item3;
    SwitchScreenItem item4;

    const std::array<std::reference_wrapper<const MenuItem>, 5> carr{{
        std::cref<MenuItem>(item0),
        std::cref<MenuItem>(item1),
        std::cref<MenuItem>(item2),
        std::cref<MenuItem>(item3),
        std::cref<MenuItem>(item4)
    }};
};
}
