#pragma once

#include "menudisplay.h"
#include "staticmenudefinition.h"
#include "utils.h"
#include "menuitem.h"
#include "actions/switchscreenaction.h"
#include "icons/back.h"
#include "texts.h"

namespace {
class StarfieldDisplay;
class PingPongDisplay;
class SpiroDisplay;
class GameOfLifeDisplay;
class MetersDisplay;
class MatrixDisplay;
class MainMenu;
}

namespace {
class DemosMenu :
    public MenuDisplay,
    public StaticText<TEXT_DEMOS>,
    public StaticMenuDefinition<
        makeComponent<MenuItem, StaticText<TEXT_STARFIELD>,  SwitchScreenAction<StarfieldDisplay>>,
        makeComponent<MenuItem, StaticText<TEXT_PINGPONG>,   SwitchScreenAction<PingPongDisplay>>,
        makeComponent<MenuItem, StaticText<TEXT_SPIRO>,      SwitchScreenAction<SpiroDisplay>>,
        makeComponent<MenuItem, StaticText<TEXT_GAMEOFLIFE>, SwitchScreenAction<GameOfLifeDisplay>>,
        makeComponent<MenuItem, StaticText<TEXT_METERS>,     SwitchScreenAction<MetersDisplay>>,
        makeComponent<MenuItem, StaticText<TEXT_MATRIX>,     SwitchScreenAction<MatrixDisplay>>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,       SwitchScreenAction<MainMenu>, StaticMenuItemIcon<&icons::back>>
    >
{};
}
