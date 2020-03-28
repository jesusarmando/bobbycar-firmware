#pragma once

#include <array>

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"
#include "displays/statusdisplay.h"
#include "displays/menus/settingsmenu.h"
#include "displays/menus/demosmenu.h"
#include "displays/menus/buzzermenu.h"
#include "changevaluedisplay.h"
#include "menuitems/rebootitem.h"
#include "texts.h"
#include "globals.h"

namespace {
struct FrontLedAccessor { static auto &getRef() { return front.command.led; } };
template<typename Tscreen>
using FrontLedChangeScreen = ChangeValueDisplay<bool, FrontLedAccessor, Tscreen, TEXT_SETFRONTLED>;

struct BackLedAccessor { static auto &getRef() { return back.command.led; } };
template<typename Tscreen>
using BackLedChangeScreen = ChangeValueDisplay<bool, BackLedAccessor, Tscreen, TEXT_SETBACKLED>;

class MainMenu final : public MenuDisplay<
    TEXT_MAINMENU,
    SwitchScreenMenuItem<StatusDisplay<MainMenu>, TEXT_STATUS>,
    SwitchScreenMenuItem<SettingsMenu<MainMenu>, TEXT_SETTINGS>,
    SwitchScreenMenuItem<DemosMenu<MainMenu>, TEXT_DEMOS>,
    SwitchScreenMenuItem<BuzzerMenu<MainMenu>, TEXT_BUZZER>,
    SwitchScreenMenuItem<FrontLedChangeScreen<MainMenu>, TEXT_SETFRONTLED>,
    SwitchScreenMenuItem<BackLedChangeScreen<MainMenu>, TEXT_SETBACKLED>,
    RebootItem
>
{};
};
