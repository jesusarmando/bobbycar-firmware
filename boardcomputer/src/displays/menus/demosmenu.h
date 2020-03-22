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
    DemosMenu(Display &prevDisplay);

    const char *displayName() const override { return "DemosMenu"; }
    const char *menuTitle() const override { return "Demos"; }

    const std::reference_wrapper<const MenuItem> *begin() const override { return std::begin(carr); };
    const std::reference_wrapper<const MenuItem> *end() const override { return std::end(carr); };

private:
    StarfieldDisplay m_starfield{*this};
    PingPongDisplay m_pingPong{*this};
    SpiroDisplay m_spiro{*this};
    GameOfLifeDisplay m_gameOfLife{*this};
    MetersDisplay m_meters{*this};

    SwitchScreenItem item0{m_starfield, m_starfield.displayName()};
    SwitchScreenItem item1{m_pingPong, m_pingPong.displayName()};
    SwitchScreenItem item2{m_spiro, m_spiro.displayName()};
    SwitchScreenItem item3{m_gameOfLife, m_gameOfLife.displayName()};
    SwitchScreenItem item4{m_meters, m_meters.displayName()};
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

DemosMenu::DemosMenu(Display &prevDisplay) :
    item5{prevDisplay, "Back"}
{
}
}
