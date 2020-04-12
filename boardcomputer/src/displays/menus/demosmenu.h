#pragma once

#include "staticmenudisplay.h"
#include "utils.h"
#include "changevaluedisplay.h"
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
    public StaticText<TEXT_DEMOS>,
    public StaticMenuDisplay<
        makeComponent<MenuItem, StaticText<TEXT_STARFIELD>,  DefaultFont, DefaultColor, SwitchScreenAction<StarfieldDisplay<DemosMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_PINGPONG>,   DefaultFont, DefaultColor, SwitchScreenAction<PingPongDisplay<DemosMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_SPIRO>,      DefaultFont, DefaultColor, SwitchScreenAction<SpiroDisplay<DemosMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_GAMEOFLIFE>, DefaultFont, DefaultColor, SwitchScreenAction<GameOfLifeDisplay<DemosMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_METERS>,     DefaultFont, DefaultColor, SwitchScreenAction<MetersDisplay<DemosMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_MATRIX>,     DefaultFont, DefaultColor, SwitchScreenAction<MatrixDisplay<DemosMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,       DefaultFont, DefaultColor, SwitchScreenAction<Tscreen>, StaticMenuItemIcon<&icons::back>>
    >
{};
}
