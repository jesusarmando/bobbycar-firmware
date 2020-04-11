#pragma once

#include "staticmenudisplay.h"
#include "menuitems/staticswitchscreenmenuitem.h"
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
class MainMenu final :
    public StaticTitle<TEXT_MAINMENU>,
    public StaticMenuDisplay<
        StaticSwitchScreenMenuItem<StatusDisplay<MainMenu>, TEXT_STATUS>,
        StaticSwitchScreenMenuItem<SelectModeMenu<MainMenu>, TEXT_SELECTMODE>,
        StaticSwitchScreenMenuItem<PresetsMenu<MainMenu>, TEXT_PRESETS>,
        StaticSwitchScreenMenuItem<SettingsMenu<MainMenu>, TEXT_SETTINGS>,
        StaticSwitchScreenMenuItem<Lockscreen<MainMenu>, TEXT_LOCKVEHICLE>,
        StaticSwitchScreenMenuItem<DemosMenu<MainMenu>, TEXT_DEMOS>,
        StaticSwitchScreenMenuItem<PoweroffDisplay<MainMenu>, TEXT_POWEROFF>,
        StaticSwitchScreenMenuItem<DebugMenu<MainMenu>, TEXT_DEBUG>
    >
{};
};
