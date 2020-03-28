#pragma once

#include <array>

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"
#include "displays/starfielddisplay.h"
#include "displays/pingpongdisplay.h"
#include "displays/spirodisplay.h"
#include "displays/gameoflifedisplay.h"
#include "displays/metersdisplay.h"
#include "texts.h"

namespace {
template<typename Tscreen>
class DemosMenu final : public MenuDisplay<
    TEXT_DEMOS,
    SwitchScreenMenuItem<StarfieldDisplay<DemosMenu<Tscreen>>, TEXT_STARFIELD>,
    SwitchScreenMenuItem<PingPongDisplay<DemosMenu<Tscreen>>, TEXT_PINGPONG>,
    SwitchScreenMenuItem<SpiroDisplay<DemosMenu<Tscreen>>, TEXT_SPIRO>,
    SwitchScreenMenuItem<GameOfLifeDisplay<DemosMenu<Tscreen>>, TEXT_GAMEOFLIFE>,
    SwitchScreenMenuItem<MetersDisplay<DemosMenu<Tscreen>>, TEXT_METERS>,
    SwitchScreenMenuItem<Tscreen, TEXT_BACK>
>
{};
}
