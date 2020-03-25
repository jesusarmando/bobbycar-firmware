#pragma once

#include <array>

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"
#include "changevaluedisplay.h"
#include "menuitems/rebootitem.h"
#include "texts.h"
#include "globals.h"

namespace {
class StatusDisplay;
class SettingsMenu;
class DemosMenu;
class BuzzerMenu;
}

namespace {
struct FrontLedAccessor
{
    static auto getValue() { return front.command.led; }
    template<typename T> static void setValue(T value) { front.command.led = value; }
};
struct BackLedAccessor
{
    static auto getValue() { return back.command.led; }
    template<typename T> static void setValue(T value) { back.command.led = value; }
};

class MainMenu final : public MenuDisplay<
    TEXT_MAINMENU,
    SwitchScreenMenuItem<StatusDisplay, TEXT_STATUS>,
    SwitchScreenMenuItem<SettingsMenu, TEXT_SETTINGS>,
    SwitchScreenMenuItem<DemosMenu, TEXT_DEMOS>,
    SwitchScreenMenuItem<BuzzerMenu, TEXT_BUZZER>,
    SwitchScreenMenuItem<ChangeValueDisplay<bool, FrontLedAccessor, MainMenu, TEXT_SETFRONTLED>, TEXT_SETFRONTLED>,
    SwitchScreenMenuItem<ChangeValueDisplay<bool, BackLedAccessor, MainMenu, TEXT_SETBACKLED>, TEXT_SETBACKLED>,
    RebootItem
>
{};
};
