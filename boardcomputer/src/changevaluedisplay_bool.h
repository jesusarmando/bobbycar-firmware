#pragma once

#include <array>

#include "changevaluedisplay.h"
#include "menudisplay.h"
#include "menuitems/setvaluemenuitem.h"
#include "menuitems/switchscreenmenuitem.h"
#include "texts.h"

namespace {
template<typename Tdisplay, const char *Ttext>
class ChangeValueDisplay<bool, Tdisplay, Ttext> : public MenuDisplay<Ttext>
{
public:
    ChangeValueDisplay(bool &value);

    void start() override;

    const std::reference_wrapper<const MenuItemInterface> *begin() const override { return std::begin(carr); };
    const std::reference_wrapper<const MenuItemInterface> *end() const override { return std::end(carr); };

private:
    bool &m_value;

    SetValueMenuItem<bool, true, Tdisplay, TEXT_TRUE> item0;
    SetValueMenuItem<bool, false, Tdisplay, TEXT_FALSE> item1;
    SwitchScreenMenuItem<Tdisplay, TEXT_BACK> item2;

    const std::array<std::reference_wrapper<const MenuItemInterface>, 3> carr{{
        std::cref<MenuItemInterface>(item0),
        std::cref<MenuItemInterface>(item1),
        std::cref<MenuItemInterface>(item2)
    }};
};

template<typename Tdisplay, const char *Ttext>
ChangeValueDisplay<bool, Tdisplay, Ttext>::ChangeValueDisplay(bool &value) :
    m_value{value},
    item0{value},
    item1{value}
{
}

template<typename Tdisplay, const char *Ttext>
void ChangeValueDisplay<bool, Tdisplay, Ttext>::start()
{
    MenuDisplay<Ttext>::start();

    if (m_value == true)
        MenuDisplayInterface::m_current = begin() + 0;
    else if (m_value == false)
        MenuDisplayInterface::m_current = begin() + 1;
}
}
