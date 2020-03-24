#pragma once

#include <array>

#include "changevaluedisplay.h"
#include "menudisplay.h"
#include "menuitems/setvaluemenuitem.h"
#include "menuitems/switchscreenmenuitem.h"
#include "modes/defaultmode.h"
#include "modes/manualmode.h"

namespace {
template<typename TnextDisplay>
class ChangeValueDisplay<ControlMode, TnextDisplay> : public MenuDisplay
{
public:
    ChangeValueDisplay(ControlMode &value);

    void start() override;

    const char *title() const override { return "Set control mode"; }

    const std::reference_wrapper<const MenuItem> *begin() const override { return std::begin(carr); };
    const std::reference_wrapper<const MenuItem> *end() const override { return std::end(carr); };

private:
    ControlMode &m_value;

    SetValueMenuItem<ControlMode, ControlMode::OpenMode, TnextDisplay> item0;
    SetValueMenuItem<ControlMode, ControlMode::Voltage, TnextDisplay> item1;
    SetValueMenuItem<ControlMode, ControlMode::Speed, TnextDisplay> item2;
    SetValueMenuItem<ControlMode, ControlMode::Torque, TnextDisplay> item3;
    SwitchScreenItem<TnextDisplay> item4{"Back"};

    const std::array<std::reference_wrapper<const MenuItem>, 5> carr{{
        std::cref<MenuItem>(item0),
        std::cref<MenuItem>(item1),
        std::cref<MenuItem>(item2),
        std::cref<MenuItem>(item3),
        std::cref<MenuItem>(item4)
    }};
};

template<typename TnextDisplay>
ChangeValueDisplay<ControlMode, TnextDisplay>::ChangeValueDisplay(ControlMode &value) :
    m_value{value},
    item0{value, "Open mode"},
    item1{value, "Voltage"},
    item2{value, "Speed"},
    item3{value, "Torque"}
{
}

template<typename TnextDisplay>
void ChangeValueDisplay<ControlMode, TnextDisplay>::start()
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
}
