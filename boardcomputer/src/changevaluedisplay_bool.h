#pragma once

#include <array>

#include "changevaluedisplay.h"
#include "menudisplay.h"
#include "menuitems/setvaluemenuitem.h"
#include "menuitems/switchscreenmenuitem.h"
#include "modes/defaultmode.h"

namespace {
template<typename TnextDisplay>
class ChangeValueDisplay<bool, TnextDisplay> : public MenuDisplay
{
public:
    ChangeValueDisplay(const char *title, bool &value);

    void start() override;

    const char *title() const override { return m_title; }

    const std::reference_wrapper<const MenuItem> *begin() const override { return std::begin(carr); };
    const std::reference_wrapper<const MenuItem> *end() const override { return std::end(carr); };

private:
    const char * const m_title;

    bool &m_value;

    SetValueMenuItem<bool, true, TnextDisplay> item0;
    SetValueMenuItem<bool, false, TnextDisplay> item1;
    SwitchScreenMenuItem<TnextDisplay> item2{"Back"};

    const std::array<std::reference_wrapper<const MenuItem>, 3> carr{{
        std::cref<MenuItem>(item0),
        std::cref<MenuItem>(item1),
        std::cref<MenuItem>(item2)
    }};
};

template<typename TnextDisplay>
ChangeValueDisplay<bool, TnextDisplay>::ChangeValueDisplay(const char *title, bool &value) :
    m_title{title},
    m_value{value},
    item0{value, "true"},
    item1{value, "false"}
{
}

template<typename TnextDisplay>
void ChangeValueDisplay<bool, TnextDisplay>::start()
{
    MenuDisplay::start();

    if (m_value == true)
        m_current = begin() + 0;
    else if (m_value == false)
        m_current = begin() + 1;
}
}
