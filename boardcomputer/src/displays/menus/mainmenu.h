#pragma once

#include <array>

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"
#include "changevaluedisplay.h"
#include "menuitems/rebootitem.h"
#include "texts.h"
#include "globals.h"

namespace {
template<typename T> class StatusDisplay;
class SettingsMenu;
class DemosMenu;
class BuzzerMenu;
}

namespace {
struct FrontLedAccessor { static auto &getRef() { return front.command.led; } };
struct BackLedAccessor { static auto &getRef() { return back.command.led; } };

class MainMenu final : public MenuDisplay<
    TEXT_MAINMENU,
    SwitchScreenMenuItem<StatusDisplay<MainMenu>, TEXT_STATUS>,
    SwitchScreenMenuItem<SettingsMenu, TEXT_SETTINGS>,
    SwitchScreenMenuItem<DemosMenu, TEXT_DEMOS>,
    SwitchScreenMenuItem<BuzzerMenu, TEXT_BUZZER>,
    SwitchScreenMenuItem<ChangeValueDisplay<bool, FrontLedAccessor, MainMenu, TEXT_SETFRONTLED>, TEXT_SETFRONTLED>,
    SwitchScreenMenuItem<ChangeValueDisplay<bool, BackLedAccessor, MainMenu, TEXT_SETBACKLED>, TEXT_SETBACKLED>,
    RebootItem
>
{};
};
