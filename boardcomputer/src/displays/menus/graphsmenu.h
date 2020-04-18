#pragma once

#include "menudisplay.h"
#include "staticmenudefinition.h"
#include "utils.h"
#include "actions/switchscreenaction.h"
#include "icons/back.h"
#include "texts.h"
#include "displays/graphdisplay.h"
#include "statistics.h"

namespace {
class MainMenu;
class DualGraphDisplay;
class MultiGraphDisplay;
}

namespace {
using GasGraphDisplay = makeComponent<GraphDisplay, StaticText<TEXT_GAS>, GasStatistics>;
using BremsGraphDisplay = makeComponent<GraphDisplay, StaticText<TEXT_BREMS>, BremsStatistics>;
using AvgSpeedGraphDisplay = makeComponent<GraphDisplay, StaticText<TEXT_AVGSPEED>, AvgSpeedStatistics>;
using AvgSpeedKmhGraphDisplay = makeComponent<GraphDisplay, StaticText<TEXT_AVGSPEEDKMH>, AvgSpeedKmhStatistics>;
using SumCurrentGraphDisplay = makeComponent<GraphDisplay, StaticText<TEXT_SUMCURRENT>, SumCurrentStatistics>;
using FrontVoltageGraphDisplay = makeComponent<GraphDisplay, StaticText<TEXT_FRONTVOLTAGE>, FrontVoltageStatistics>;
using BackVoltageGraphDisplay = makeComponent<GraphDisplay, StaticText<TEXT_BACKVOLTAGE>, BackVoltageStatistics>;

class GraphsMenu :
    public MenuDisplay,
    public StaticText<TEXT_GRAPHS>,
    public StaticMenuDefinition<
        makeComponent<MenuItem, StaticText<TEXT_GAS>,  SwitchScreenAction<GasGraphDisplay>>,
        makeComponent<MenuItem, StaticText<TEXT_BREMS>,  SwitchScreenAction<BremsGraphDisplay>>,
        makeComponent<MenuItem, StaticText<TEXT_AVGSPEED>,  SwitchScreenAction<AvgSpeedGraphDisplay>>,
        makeComponent<MenuItem, StaticText<TEXT_AVGSPEEDKMH>,  SwitchScreenAction<AvgSpeedKmhGraphDisplay>>,
        makeComponent<MenuItem, StaticText<TEXT_SUMCURRENT>,  SwitchScreenAction<SumCurrentGraphDisplay>>,
        makeComponent<MenuItem, StaticText<TEXT_FRONTVOLTAGE>,  SwitchScreenAction<FrontVoltageGraphDisplay>>,
        makeComponent<MenuItem, StaticText<TEXT_BACKVOLTAGE>,  SwitchScreenAction<BackVoltageGraphDisplay>>,
        makeComponent<MenuItem, StaticText<TEXT_DUALGRAPHS>,  SwitchScreenAction<DualGraphDisplay>>,
        makeComponent<MenuItem, StaticText<TEXT_MULTIGRAPHS>,  SwitchScreenAction<MultiGraphDisplay>>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,      SwitchScreenAction<MainMenu>, StaticMenuItemIcon<&icons::back>>
    >
{};
}
