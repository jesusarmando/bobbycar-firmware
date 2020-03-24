#pragma once

#include <array>

#include "menudisplay.h"
#include "changevaluedisplay.h"
#include "globals.h"
#include "menuitems/switchscreenmenuitem.h"

namespace {
class PotiSettingsMenu final : public MenuDisplay
{
public:
    PotiSettingsMenu(Display &prevDisplay);

    const char *title() const override { return "Poti settings"; }

    const std::reference_wrapper<const MenuItem> *begin() const override { return std::begin(carr); };
    const std::reference_wrapper<const MenuItem> *end() const override { return std::end(carr); };

private:
    ChangeValueDisplay<uint16_t> m_gasMinDisplay{"gasMin", gasMin, *this};
    ChangeValueDisplay<uint16_t> m_gasMaxDisplay{"gasMax", gasMax, *this};
    ChangeValueDisplay<uint16_t> m_bremsMinDisplay{"bremsMin", bremsMin, *this};
    ChangeValueDisplay<uint16_t> m_bremsMaxDisplay{"bremsMax", bremsMax, *this};

    SwitchScreenItem item0{m_gasMinDisplay, m_gasMinDisplay.title()};
    SwitchScreenItem item1{m_gasMaxDisplay, m_gasMaxDisplay.title()};
    SwitchScreenItem item2{m_bremsMinDisplay, m_bremsMinDisplay.title()};
    SwitchScreenItem item3{m_bremsMaxDisplay, m_bremsMaxDisplay.title()};
    SwitchScreenItem item4;

    const std::array<std::reference_wrapper<const MenuItem>, 5> carr{{
        std::cref<MenuItem>(item0),
        std::cref<MenuItem>(item1),
        std::cref<MenuItem>(item2),
        std::cref<MenuItem>(item3),
        std::cref<MenuItem>(item4)
    }};
};

PotiSettingsMenu::PotiSettingsMenu(Display &prevDisplay):
   item4{prevDisplay, "Back"}
{
}
}
