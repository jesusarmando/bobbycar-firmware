#pragma once

#include <array>

#include "changevaluedisplay.h"
#include "menudisplay.h"
#include "menuitems/setvaluemenuitem.h"
#include "menuitems/switchscreenmenuitem.h"
#include "texts.h"

namespace {
template<typename Tdisplay, const char *Ttext>
class ChangeValueDisplay<ControlType, Tdisplay, Ttext> : public MenuDisplay<Ttext>
{
public:
    ChangeValueDisplay(ControlType &value);

    void start() override;

    const std::reference_wrapper<const MenuItemInterface> *begin() const override { return std::begin(carr); };
    const std::reference_wrapper<const MenuItemInterface> *end() const override { return std::end(carr); };

private:
    ControlType &m_value;

    SetValueMenuItem<ControlType, ControlType::Commutation, Tdisplay, TEXT_COMMUTATION> item0;
    SetValueMenuItem<ControlType, ControlType::Sinusoidal, Tdisplay, TEXT_SINUSOIDAL> item1;
    SetValueMenuItem<ControlType, ControlType::FieldOrientedControl, Tdisplay, TEXT_FIELDORIENTEDCONTROL> item2;
    SwitchScreenMenuItem<Tdisplay, TEXT_BACK> item3;

    const std::array<std::reference_wrapper<const MenuItemInterface>, 4> carr{{
        std::cref<MenuItemInterface>(item0),
        std::cref<MenuItemInterface>(item1),
        std::cref<MenuItemInterface>(item2),
        std::cref<MenuItemInterface>(item3)
    }};
};

template<typename Tdisplay, const char *Ttext>
ChangeValueDisplay<ControlType, Tdisplay, Ttext>::ChangeValueDisplay(ControlType &value) :
    m_value{value},
    item0{value},
    item1{value},
    item2{value}
{
}

template<typename Tdisplay, const char *Ttext>
void ChangeValueDisplay<ControlType, Tdisplay, Ttext>::start()
{
    MenuDisplay<Ttext>::start();

    if (m_value == ControlType::Commutation)
        MenuDisplayInterface::m_current = begin() + 0;
    else if (m_value == ControlType::Sinusoidal)
        MenuDisplayInterface::m_current = begin() + 1;
    else if (m_value == ControlType::FieldOrientedControl)
        MenuDisplayInterface::m_current = begin() + 2;
    else
        MenuDisplayInterface::m_current = begin() + 3;
}
}
