#pragma once

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"
#include "displays/statusdisplay.h"
#include "displays/menus/selectmodemenu.h"
#include "displays/menus/presetsmenu.h"
#include "displays/menus/settingsmenu.h"
#include "displays/lockscreen.h"
#include "displays/menus/demosmenu.h"
#include "displays/poweroffdisplay.h"
#include "displays/menus/debugmenu.h"
#include "texts.h"

namespace {
class MainMenu final : public MenuDisplay<
    TEXT_MAINMENU,
    SwitchScreenMenuItem<StatusDisplay<MainMenu>, TEXT_STATUS>,
    SwitchScreenMenuItem<SelectModeMenu<MainMenu>, TEXT_SELECTMODE>,
    SwitchScreenMenuItem<PresetsMenu<MainMenu>, TEXT_PRESETS>,
    SwitchScreenMenuItem<SettingsMenu<MainMenu>, TEXT_SETTINGS>,
    SwitchScreenMenuItem<Lockscreen<MainMenu>, TEXT_LOCKVEHICLE>,
    SwitchScreenMenuItem<DemosMenu<MainMenu>, TEXT_DEMOS>,
    SwitchScreenMenuItem<PoweroffDisplay<MainMenu>, TEXT_POWEROFF>,
    SwitchScreenMenuItem<DebugMenu<MainMenu>, TEXT_DEBUG>
>
{};
};
