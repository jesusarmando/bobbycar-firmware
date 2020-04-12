#pragma once

#include "menudisplay.h"
#include "staticmenudefinition.h"
#include "menuitem.h"
#include "actions/switchscreenaction.h"
#include "texts.h"
#include "icons/back.h"

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
        makeComponent<MenuItem, StaticText<TEXT_STATUS>,      DefaultFont, DefaultColor, SwitchScreenAction<StatusDisplay<MainMenu>>, StaticMenuItemIcon<&icons::back>>,
        makeComponent<MenuItem, StaticText<TEXT_SELECTMODE>,  DefaultFont, DefaultColor, SwitchScreenAction<SelectModeMenu<MainMenu>>>,
        makeComponent<MenuItem, StaticText<TEXT_PRESETS>,     DefaultFont, DefaultColor, SwitchScreenAction<PresetsMenu<MainMenu>>>,
        makeComponent<MenuItem, StaticText<TEXT_SETTINGS>,    DefaultFont, DefaultColor, SwitchScreenAction<SettingsMenu<MainMenu>>>,
        makeComponent<MenuItem, StaticText<TEXT_LOCKVEHICLE>, DefaultFont, DefaultColor, SwitchScreenAction<Lockscreen<MainMenu>>>,
        makeComponent<MenuItem, StaticText<TEXT_DEMOS>,       DefaultFont, DefaultColor, SwitchScreenAction<DemosMenu<MainMenu>>>,
        makeComponent<MenuItem, StaticText<TEXT_POWEROFF>,    DefaultFont, DefaultColor, SwitchScreenAction<PoweroffDisplay<MainMenu>>>,
        makeComponent<MenuItem, StaticText<TEXT_DEBUG>,       DefaultFont, DefaultColor, SwitchScreenAction<DebugMenu<MainMenu>>>
    >
{};
};
