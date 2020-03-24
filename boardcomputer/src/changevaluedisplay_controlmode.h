#pragma once

#include <array>

#include "changevaluedisplay.h"
#include "globals.h"
#include "menudisplay.h"
#include "menuitems/setvaluemenuitem.h"
#include "menuitems/switchscreenmenuitem.h"

namespace {
template<>
class ChangeValueDisplay<ControlMode> final : public MenuDisplay
{
public:
    ChangeValueDisplay(const char *title, ControlMode &controlMode, Display &prevDisplay) :
        m_title{title},
        m_controlMode{controlMode},
        item0{ControlMode::OpenMode, controlMode, prevDisplay, "Open mode"},
        item1{ControlMode::Voltage, controlMode, prevDisplay, "Voltage"},
        item2{ControlMode::Speed, controlMode, prevDisplay, "Speed"},
        item3{ControlMode::Torque, controlMode, prevDisplay, "Torque"},
        item4{prevDisplay, "Back"}
    {
    }

    void start() override
    {
        MenuDisplay::start();

        if (m_controlMode == ControlMode::OpenMode)
            m_current = begin() + 0;
        else if (m_controlMode == ControlMode::Voltage)
            m_current = begin() + 1;
        else if (m_controlMode == ControlMode::Speed)
            m_current = begin() + 2;
        else if (m_controlMode == ControlMode::Torque)
            m_current = begin() + 3;
        else
            m_current = begin() + 4;
    }

    const char *menuTitle() const override { return m_title; }

    const std::reference_wrapper<const MenuItem> *begin() const override { return std::begin(carr); };
    const std::reference_wrapper<const MenuItem> *end() const override { return std::end(carr); };

private:
    const char * const m_title;

    ControlMode &m_controlMode;

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
