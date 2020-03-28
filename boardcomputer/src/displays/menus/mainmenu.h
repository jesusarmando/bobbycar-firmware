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
struct BackLedAccessor { static auto &getRef() { return back.command.led; } };

class MainMenu final : public MenuDisplay<
    TEXT_MAINMENU,
    SwitchScreenMenuItem<StatusDisplay<MainMenu>, TEXT_STATUS>,
    SwitchScreenMenuItem<SettingsMenu<MainMenu>, TEXT_SETTINGS>,
    SwitchScreenMenuItem<DemosMenu<MainMenu>, TEXT_DEMOS>,
    SwitchScreenMenuItem<BuzzerMenu<MainMenu>, TEXT_BUZZER>,
    SwitchScreenMenuItem<ChangeValueDisplay<bool, FrontLedAccessor, MainMenu, TEXT_SETFRONTLED>, TEXT_SETFRONTLED>,
    SwitchScreenMenuItem<ChangeValueDisplay<bool, BackLedAccessor, MainMenu, TEXT_SETBACKLED>, TEXT_SETBACKLED>,
    RebootItem
>
{};
};
