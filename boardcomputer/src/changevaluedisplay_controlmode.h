#pragma once

#include <array>

#include "changevaluedisplay.h"
#include "menudisplay.h"
#include "menuitems/setvaluemenuitem.h"
#include "menuitems/switchscreenmenuitem.h"
#include "texts.h"

namespace {
template<typename Tdisplay, const char *Ttext>
class ChangeValueDisplay<ControlMode, Tdisplay, Ttext> : public MenuDisplay<Ttext>
{
public:
    ChangeValueDisplay(ControlMode &value);

    void start() override;

    const std::reference_wrapper<const MenuItemInterface> *begin() const override { return std::begin(carr); };
    const std::reference_wrapper<const MenuItemInterface> *end() const override { return std::end(carr); };

private:
    ControlMode &m_value;

    SetValueMenuItem<ControlMode, ControlMode::OpenMode, Tdisplay, TEXT_OPENMODE> item0;
    SetValueMenuItem<ControlMode, ControlMode::Voltage, Tdisplay, TEXT_VOLTAGE> item1;
    SetValueMenuItem<ControlMode, ControlMode::Speed, Tdisplay, TEXT_SPEED> item2;
    SetValueMenuItem<ControlMode, ControlMode::Torque, Tdisplay, TEXT_TORQUE> item3;
    SwitchScreenMenuItem<Tdisplay, TEXT_BACK> item4;

    const std::array<std::reference_wrapper<const MenuItemInterface>, 5> carr{{
        std::cref<MenuItemInterface>(item0),
        std::cref<MenuItemInterface>(item1),
        std::cref<MenuItemInterface>(item2),
        std::cref<MenuItemInterface>(item3),
        std::cref<MenuItemInterface>(item4)
    }};
};

template<typename Tdisplay, const char *Ttext>
ChangeValueDisplay<ControlMode, Tdisplay, Ttext>::ChangeValueDisplay(ControlMode &value) :
    m_value{value},
    item0{value},
    item1{value},
    item2{value},
    item3{value}
{
}

template<typename Tdisplay, const char *Ttext>
void ChangeValueDisplay<ControlMode, Tdisplay, Ttext>::start()
{
    MenuDisplay<Ttext>::start();

    if (m_value == ControlMode::OpenMode)
        MenuDisplayInterface::m_current = begin() + 0;
    else if (m_value == ControlMode::Voltage)
        MenuDisplayInterface::m_current = begin() + 1;
    else if (m_value == ControlMode::Speed)
        MenuDisplayInterface::m_current = begin() + 2;
    else if (m_value == ControlMode::Torque)
        MenuDisplayInterface::m_current = begin() + 3;
    else
        MenuDisplayInterface::m_current = begin() + 4;
}
}
