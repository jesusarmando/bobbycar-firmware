#pragma once

#include "menudisplay.h"
#include "changevaluedisplay.h"
#include "menuitems/switchscreenmenuitem.h"

namespace {
class BuzzerMenu : public MenuDisplay
{
public:
    BuzzerMenu(Display &prevDisplay);

    const char *title() const override { return "Buzzer"; }
    const std::reference_wrapper<const MenuItem> *begin() const override { return std::begin(carr); }
    const std::reference_wrapper<const MenuItem> *end() const override { return std::end(carr); }

private:
    ChangeValueDisplay<uint8_t> m_frontFreq{"Front freq", front.command.buzzer.freq, *this};
    ChangeValueDisplay<uint8_t> m_frontPattern{"Front pattern", front.command.buzzer.pattern, *this};
    ChangeValueDisplay<uint8_t> m_backFreq{"Back freq", back.command.buzzer.freq, *this};
    ChangeValueDisplay<uint8_t> m_backPattern{"Back pattern", back.command.buzzer.pattern, *this};

    SwitchScreenItem item0{m_frontFreq, m_frontFreq.title()};
    SwitchScreenItem item1{m_frontPattern, m_frontPattern.title()};
    SwitchScreenItem item2{m_backFreq, m_backFreq.title()};
    SwitchScreenItem item3{m_backPattern, m_backPattern.title()};
    SwitchScreenItem item4;

    const std::array<std::reference_wrapper<const MenuItem>, 5> carr{{
        std::cref<MenuItem>(item0),
        std::cref<MenuItem>(item1),
        std::cref<MenuItem>(item2),
        std::cref<MenuItem>(item3),
        std::cref<MenuItem>(item4)
    }};
};

BuzzerMenu::BuzzerMenu(Display &prevDisplay) :
    item4{prevDisplay, "Back"}
{
}
}
