#pragma once

#include <array>

#include "menudisplay.h"
#include "changevaluedisplay.h"
#include "globals.h"
#include "menuitems/switchscreenmenuitem.h"

namespace {
class EnableMenu final : public MenuDisplay
{
public:
    EnableMenu(Display &prevDisplay);

    const char *menuTitle() const override { return "Enable"; }

    const std::reference_wrapper<const MenuItem> *begin() const override { return std::begin(carr); };
    const std::reference_wrapper<const MenuItem> *end() const override { return std::end(carr); };

private:
    ChangeValueDisplay<bool> m_frontLeft{"Enable front left", front.command.left.enable, *this};
    ChangeValueDisplay<bool> m_frontRight{"Enable front right", front.command.right.enable, *this};
    ChangeValueDisplay<bool> m_backLeft{"Enable back left", back.command.left.enable, *this};
    ChangeValueDisplay<bool> m_backRight{"Enable back right", back.command.right.enable, *this};

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
