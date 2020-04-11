#pragma once

#include "staticmenudisplay.h"
#include "menuitems/staticswitchscreenmenuitem.h"
#include "displays/starfielddisplay.h"
#include "displays/pingpongdisplay.h"
#include "displays/spirodisplay.h"
#include "displays/gameoflifedisplay.h"
#include "displays/metersdisplay.h"
#include "displays/matrixdisplay.h"
#include "texts.h"

namespace {
template<typename Tscreen>
class DemosMenu final :
    public StaticTitle<TEXT_DEMOS>,
    public StaticMenuDisplay<
        StaticSwitchScreenMenuItem<StarfieldDisplay<DemosMenu<Tscreen>>, TEXT_STARFIELD>,
        StaticSwitchScreenMenuItem<PingPongDisplay<DemosMenu<Tscreen>>, TEXT_PINGPONG>,
        StaticSwitchScreenMenuItem<SpiroDisplay<DemosMenu<Tscreen>>, TEXT_SPIRO>,
        StaticSwitchScreenMenuItem<GameOfLifeDisplay<DemosMenu<Tscreen>>, TEXT_GAMEOFLIFE>,
        StaticSwitchScreenMenuItem<MetersDisplay<DemosMenu<Tscreen>>, TEXT_METERS>,
        StaticSwitchScreenMenuItem<MatrixDisplay<DemosMenu<Tscreen>>, TEXT_MATRIX>,
        StaticSwitchScreenMenuItem<Tscreen, TEXT_BACK>
    >
{};
}
