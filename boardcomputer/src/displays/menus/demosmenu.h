#pragma once

#include <array>

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"

namespace {
class StarfieldDisplay;
class PingPongDisplay;
class SpiroDisplay;
class GameOfLifeDisplay;
class MetersDisplay;
class MainMenu;
}

namespace {
class DemosMenu final : public MenuDisplay
{
public:
    const char *title() const override { return "Demos"; }

    const std::reference_wrapper<const MenuItem> *begin() const override { return std::begin(carr); };
    const std::reference_wrapper<const MenuItem> *end() const override { return std::end(carr); };

private:
    SwitchScreenMenuItem<StarfieldDisplay> item0{"Starfield"};
    SwitchScreenMenuItem<PingPongDisplay> item1{"PingPong"};
    SwitchScreenMenuItem<SpiroDisplay> item2{"Spiro"};
    SwitchScreenMenuItem<GameOfLifeDisplay> item3{"GameOfLife"};
    SwitchScreenMenuItem<MetersDisplay> item4{"Meters"};
    SwitchScreenMenuItem<MainMenu> item5{"Back"};

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
