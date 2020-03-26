#pragma once

#include <array>

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"
#include "texts.h"

namespace {
template<typename T> class StarfieldDisplay;
template<typename T> class PingPongDisplay;
template<typename T> class SpiroDisplay;
template<typename T> class GameOfLifeDisplay;
template<typename T> class MetersDisplay;
class MainMenu;
}

namespace {
class DemosMenu final : public MenuDisplay<
    TEXT_DEMOS,
    SwitchScreenMenuItem<StarfieldDisplay<DemosMenu>, TEXT_STARFIELD>,
    SwitchScreenMenuItem<PingPongDisplay<DemosMenu>, TEXT_PINGPONG>,
    SwitchScreenMenuItem<SpiroDisplay<DemosMenu>, TEXT_SPIRO>,
    SwitchScreenMenuItem<GameOfLifeDisplay<DemosMenu>, TEXT_GAMEOFLIFE>,
    SwitchScreenMenuItem<MetersDisplay<DemosMenu>, TEXT_METERS>,
    SwitchScreenMenuItem<MainMenu, TEXT_BACK>
>
{};
}
