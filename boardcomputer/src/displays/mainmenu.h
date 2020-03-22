#pragma once

#include <array>

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"
#include "menuitems/rebootitem.h"

#include "displays/statusdisplay.h"
#include "displays/starfielddisplay.h"
#include "displays/pingpongdisplay.h"
#include "displays/spirodisplay.h"

namespace {
class MainMenu final : public MenuDisplay
{
public:
    const char *displayName() const override { return "MainMenu"; }

    const std::reference_wrapper<const MenuItem> *begin() const override
    {
        return std::begin(carr);
    };
    const std::reference_wrapper<const MenuItem> *end() const override
    {
        return std::end(carr);
    };

private:
    SwitchScreenItem item0{displays::status, displays::status.displayName()};
    SwitchScreenItem item1{displays::starfield, displays::starfield.displayName()};
    SwitchScreenItem item2{displays::pingPong, displays::pingPong.displayName()};
    SwitchScreenItem item3{displays::spiro, displays::spiro.displayName()};
    RebootItem item4;

    const std::array<std::reference_wrapper<const MenuItem>, 5> carr{{
        std::cref<MenuItem>(item0),
        std::cref<MenuItem>(item1),
        std::cref<MenuItem>(item2),
        std::cref<MenuItem>(item3),
        std::cref<MenuItem>(item4)
    }};
};

namespace displays {
MainMenu mainMenu;
}
};
