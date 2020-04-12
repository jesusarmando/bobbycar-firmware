#pragma once

#include "menudisplay.h"
#include "staticmenudefinition.h"
#include "menuitem.h"
#include "actions/switchscreenaction.h"
#include "texts.h"
#include "icons/back.h"
#include "icons/lock.h"

#include "displays/statusdisplay.h"
#include "displays/menus/selectmodemenu.h"
#include "displays/menus/presetsmenu.h"
#include "displays/menus/settingsmenu.h"
#include "displays/lockscreen.h"
#include "displays/menus/demosmenu.h"
#include "displays/poweroffdisplay.h"
#include "displays/menus/debugmenu.h"

namespace {
class MainMenu :
    public MenuDisplay,
    public StaticText<TEXT_MAINMENU>,
    public StaticMenuDefinition<
        makeComponent<MenuItem, StaticText<TEXT_STATUS>,      SwitchScreenAction<StatusDisplay<MainMenu>>, StaticMenuItemIcon<&icons::back>>,
        makeComponent<MenuItem, StaticText<TEXT_SELECTMODE>,  SwitchScreenAction<SelectModeMenu<MainMenu>>>,
        makeComponent<MenuItem, StaticText<TEXT_PRESETS>,     SwitchScreenAction<PresetsMenu<MainMenu>>>,
        makeComponent<MenuItem, StaticText<TEXT_SETTINGS>,    SwitchScreenAction<SettingsMenu<MainMenu>>>,
        makeComponent<MenuItem, StaticText<TEXT_LOCKVEHICLE>, SwitchScreenAction<Lockscreen<MainMenu>>, StaticMenuItemIcon<&icons::lock>>,
        makeComponent<MenuItem, StaticText<TEXT_DEMOS>,       SwitchScreenAction<DemosMenu<MainMenu>>>,
        makeComponent<MenuItem, StaticText<TEXT_POWEROFF>,    SwitchScreenAction<PoweroffDisplay<MainMenu>>>,
        makeComponent<MenuItem, StaticText<TEXT_DEBUG>,       SwitchScreenAction<DebugMenu<MainMenu>>>
    >
{};
};
