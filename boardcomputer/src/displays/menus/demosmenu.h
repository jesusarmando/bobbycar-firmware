#pragma once

#include <array>

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"

#include "displays/starfielddisplay.h"
#include "displays/pingpongdisplay.h"
#include "displays/spirodisplay.h"
#include "displays/gameoflifedisplay.h"
#include "displays/metersdisplay.h"

namespace {
class DemosMenu final : public MenuDisplay
{
public:
    DemosMenu();

    const char *displayName() const override { return "DemosMenu"; }

    const std::reference_wrapper<const MenuItem> *begin() const override
    {
        return std::begin(carr);
    };
    const std::reference_wrapper<const MenuItem> *end() const override
    {
        return std::end(carr);
    };

private:
    SwitchScreenItem item0{displays::starfield, displays::starfield.displayName()};
    SwitchScreenItem item1{displays::pingPong, displays::pingPong.displayName()};
    SwitchScreenItem item2{displays::spiro, displays::spiro.displayName()};
    SwitchScreenItem item3{displays::gameOfLife, displays::gameOfLife.displayName()};
    SwitchScreenItem item4{displays::meters, displays::meters.displayName()};
    SwitchScreenItem item5;

    const std::array<std::reference_wrapper<const MenuItem>, 6> carr{{
        std::cref<MenuItem>(item0),
        std::cref<MenuItem>(item1),
        std::cref<MenuItem>(item2),
        std::cref<MenuItem>(item3),
        std::cref<MenuItem>(item4),
        std::cref<MenuItem>(item5)
    }};
};

namespace displays {
DemosMenu demosMenu;
}
}
