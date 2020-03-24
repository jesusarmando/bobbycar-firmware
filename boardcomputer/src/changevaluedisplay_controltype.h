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
class ChangeValueDisplay<ControlType, TnextDisplay> : public MenuDisplay
{
public:
    ChangeValueDisplay(ControlType &value);

    void start() override;

    const char *title() const override { return "Set control type"; }

    const std::reference_wrapper<const MenuItem> *begin() const override { return std::begin(carr); };
    const std::reference_wrapper<const MenuItem> *end() const override { return std::end(carr); };

private:
    ControlType &m_value;

    SetValueMenuItem<ControlType, ControlType::Commutation, TnextDisplay> item0;
    SetValueMenuItem<ControlType, ControlType::Sinusoidal, TnextDisplay> item1;
    SetValueMenuItem<ControlType, ControlType::FieldOrientedControl, TnextDisplay> item2;
    SwitchScreenItem<TnextDisplay> item3{"Back"};

    const std::array<std::reference_wrapper<const MenuItem>, 4> carr{{
        std::cref<MenuItem>(item0),
        std::cref<MenuItem>(item1),
        std::cref<MenuItem>(item2),
        std::cref<MenuItem>(item3)
    }};
};

template<typename TnextDisplay>
ChangeValueDisplay<ControlType, TnextDisplay>::ChangeValueDisplay(ControlType &value) :
    m_value{value},
    item0{value, "Commutation"},
    item1{value, "Sinusoidal"},
    item2{value, "Field oriented control"}
{
}

template<typename TnextDisplay>
void ChangeValueDisplay<ControlType, TnextDisplay>::start()
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
}
