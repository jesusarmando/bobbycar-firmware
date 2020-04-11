#pragma once

#include "staticmenudisplay.h"
#include "menuitems/staticswitchscreenmenuitem.h"
#include "displays/menus/buzzermenu.h"
#include "displays/menus/dynamicdebugmenu.h"
#include "changevaluedisplay.h"
#include "texts.h"
#include "globals.h"

namespace {
struct FrontLedAccessor { static auto &getRef() { return front.command.led; } };
template<typename Tscreen>
using FrontLedChangeScreen = ChangeValueDisplay<bool, FrontLedAccessor, Tscreen, TEXT_SETFRONTLED>;

struct BackLedAccessor { static auto &getRef() { return back.command.led; } };
template<typename Tscreen>
using BackLedChangeScreen = ChangeValueDisplay<bool, BackLedAccessor, Tscreen, TEXT_SETBACKLED>;

template<typename Tscreen>
class DebugMenu final :
    public StaticTitle<TEXT_DEBUG>,
    public StaticMenuDisplay<
        StaticSwitchScreenMenuItem<BuzzerMenu<DebugMenu<Tscreen>>, TEXT_BUZZER>,
        StaticSwitchScreenMenuItem<FrontLedChangeScreen<DebugMenu<Tscreen>>, TEXT_SETFRONTLED>,
        StaticSwitchScreenMenuItem<BackLedChangeScreen<DebugMenu<Tscreen>>, TEXT_SETBACKLED>,
        StaticSwitchScreenMenuItem<DynamicDebugMenu<DebugMenu<Tscreen>>, TEXT_DYNAMICMENU>,
        StaticSwitchScreenMenuItem<Tscreen, TEXT_BACK>
    >
{};
}
