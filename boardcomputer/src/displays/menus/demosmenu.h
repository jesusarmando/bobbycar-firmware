#pragma once

#include <array>

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"

#include "displays/starfielddisplay.h"
#include "displays/pingpongdisplay.h"
#include "displays/spirodisplay.h"
#include "displays/gameoflifedisplay.h"
#include "displays/metersdisplay.h"
#include "displays/menus/mainmenu.h"

namespace {
class DemosMenu final : public MenuDisplay
{
public:
    const char *title() const override { return "Demos"; }

    const std::reference_wrapper<const MenuItem> *begin() const override { return std::begin(carr); };
    const std::reference_wrapper<const MenuItem> *end() const override { return std::end(carr); };

private:
    SwitchScreenItem<StarfieldDisplay> item0{"Starfield"};
    SwitchScreenItem<PingPongDisplay> item1{"PingPong"};
    SwitchScreenItem<SpiroDisplay> item2{"Spiro"};
    SwitchScreenItem<GameOfLifeDisplay> item3{"GameOfLife"};
    SwitchScreenItem<MetersDisplay> item4{"Meters"};
    SwitchScreenItem<MainMenu> item5{"Back"};

    const std::array<std::reference_wrapper<const MenuItem>, 6> carr{{
        std::cref<MenuItem>(item0),
        std::cref<MenuItem>(item1),
        std::cref<MenuItem>(item2),
        std::cref<MenuItem>(item3),
        std::cref<MenuItem>(item4),
        std::cref<MenuItem>(item5)
    }};
};
}
