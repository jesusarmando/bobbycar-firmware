#pragma once

#include <array>

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"
#include "texts.h"

namespace {
class StarfieldDisplay;
class PingPongDisplay;
class SpiroDisplay;
class GameOfLifeDisplay;
class MetersDisplay;
class MainMenu;
}

namespace {
class DemosMenu final : public MenuDisplay<
    TEXT_DEMOS,
    SwitchScreenMenuItem<StarfieldDisplay, TEXT_STARFIELD>,
    SwitchScreenMenuItem<PingPongDisplay, TEXT_PINGPONG>,
    SwitchScreenMenuItem<SpiroDisplay, TEXT_SPIRO>,
    SwitchScreenMenuItem<GameOfLifeDisplay, TEXT_GAMEOFLIFE>,
    SwitchScreenMenuItem<MetersDisplay, TEXT_METERS>,
    SwitchScreenMenuItem<MainMenu, TEXT_BACK>
>
{};
}
