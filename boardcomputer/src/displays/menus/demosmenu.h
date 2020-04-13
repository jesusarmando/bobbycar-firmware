#pragma once

#include "menudisplay.h"
#include "staticmenudefinition.h"
#include "utils.h"
#include "menuitem.h"
#include "actions/switchscreenaction.h"
#include "icons/back.h"
#include "texts.h"

#include "displays/starfielddisplay.h"
#include "displays/pingpongdisplay.h"
#include "displays/spirodisplay.h"
#include "displays/gameoflifedisplay.h"
#include "displays/metersdisplay.h"
#include "displays/matrixdisplay.h"

namespace {
template<typename Tscreen>
class DemosMenu :
    public MenuDisplay,
    public StaticText<TEXT_DEMOS>,
    public StaticMenuDefinition<
        makeComponent<MenuItem, StaticText<TEXT_STARFIELD>,  SwitchScreenAction<StarfieldDisplay<DemosMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_PINGPONG>,   SwitchScreenAction<PingPongDisplay<DemosMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_SPIRO>,      SwitchScreenAction<SpiroDisplay<DemosMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_GAMEOFLIFE>, SwitchScreenAction<GameOfLifeDisplay<DemosMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_METERS>,     SwitchScreenAction<MetersDisplay<DemosMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_MATRIX>,     SwitchScreenAction<MatrixDisplay<DemosMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,       SwitchScreenAction<Tscreen>, StaticMenuItemIcon<&icons::back>>
    >
{};
}
