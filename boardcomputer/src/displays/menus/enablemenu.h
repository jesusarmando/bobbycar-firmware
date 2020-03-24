#pragma once

#include <array>

#include "menudisplay.h"
#include "changevaluedisplay_bool.h"
#include "globals.h"
#include "menuitems/switchscreenmenuitem.h"

namespace {
class EnableMenu final : public MenuDisplay
{
public:
    EnableMenu(Display &prevDisplay);

    const char *title() const override { return "Enable"; }

    const std::reference_wrapper<const MenuItem> *begin() const override { return std::begin(carr); };
    const std::reference_wrapper<const MenuItem> *end() const override { return std::end(carr); };

private:
    SetFrontLeftEnabledDisplay m_frontLeft{*this};
    SetFrontRightEnabledDisplay m_frontRight{*this};
    SetBackLeftEnabledDisplay m_backLeft{*this};
    SetBackRightEnabledDisplay m_backRight{*this};

    SwitchScreenItem item0{m_frontLeft, m_frontLeft.title()};
    SwitchScreenItem item1{m_frontRight, m_frontRight.title()};
    SwitchScreenItem item2{m_backLeft, m_backLeft.title()};
    SwitchScreenItem item3{m_backRight, m_backRight.title()};
    SwitchScreenItem item4;

    const std::array<std::reference_wrapper<const MenuItem>, 5> carr{{
        std::cref<MenuItem>(item0),
        std::cref<MenuItem>(item1),
        std::cref<MenuItem>(item2),
        std::cref<MenuItem>(item3),
        std::cref<MenuItem>(item4)
    }};
};

EnableMenu::EnableMenu(Display &prevDisplay):
   item4{prevDisplay, "Back"}
{
}
}
