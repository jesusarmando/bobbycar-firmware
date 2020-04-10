#pragma once

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"
#include "displays/bluetoothstatusdisplay.h"
#include "displays/menus/buzzermenu.h"
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
class DebugMenu final : public MenuDisplay<
    TEXT_DEBUG,
    SwitchScreenMenuItem<BuzzerMenu<DebugMenu<Tscreen>>, TEXT_BUZZER>,
    SwitchScreenMenuItem<FrontLedChangeScreen<DebugMenu<Tscreen>>, TEXT_SETFRONTLED>,
    SwitchScreenMenuItem<BackLedChangeScreen<DebugMenu<Tscreen>>, TEXT_SETBACKLED>,
    SwitchScreenMenuItem<Tscreen, TEXT_BACK>
>
{};
}
