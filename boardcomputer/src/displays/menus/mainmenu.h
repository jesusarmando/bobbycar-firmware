#pragma once

#include <array>

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"
#include "menuitems/rebootitem.h"
#include "texts.h"

namespace {
class StatusDisplay;
class SettingsMenu;
class DemosMenu;
class BuzzerMenu;
class SetFrontLedDisplay;
class SetBackLedDisplay;
}

namespace {
class MainMenu final : public MenuDisplay<
    TEXT_MAINMENU,
    SwitchScreenMenuItem<StatusDisplay, TEXT_STATUS>,
    SwitchScreenMenuItem<SettingsMenu, TEXT_SETTINGS>,
    SwitchScreenMenuItem<DemosMenu, TEXT_DEMOS>,
    SwitchScreenMenuItem<BuzzerMenu, TEXT_BUZZER>,
    SwitchScreenMenuItem<SetFrontLedDisplay, TEXT_SETFRONTLED>,
    SwitchScreenMenuItem<SetBackLedDisplay, TEXT_SETBACKLED>,
    RebootItem
>
{};
};
