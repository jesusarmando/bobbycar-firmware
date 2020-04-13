#pragma once

#include "menudisplay.h"
#include "staticmenudefinition.h"
#include "menuitem.h"
#include "actions/switchscreenaction.h"
#include "texts.h"
#include "icons/back.h"
#include "icons/lock.h"

namespace {
class StatusDisplay;
class SelectModeMenu;
class PresetsMenu;
class SettingsMenu;
class Lockscreen;
class DemosMenu;
class PoweroffDisplay;
class DebugMenu;
}

namespace {
class MainMenu :
    public MenuDisplay,
    public StaticText<TEXT_MAINMENU>,
    public StaticMenuDefinition<
        makeComponent<MenuItem, StaticText<TEXT_STATUS>,      SwitchScreenAction<StatusDisplay>, StaticMenuItemIcon<&icons::back>>,
        makeComponent<MenuItem, StaticText<TEXT_SELECTMODE>,  SwitchScreenAction<SelectModeMenu>>,
        makeComponent<MenuItem, StaticText<TEXT_PRESETS>,     SwitchScreenAction<PresetsMenu>>,
        makeComponent<MenuItem, StaticText<TEXT_SETTINGS>,    SwitchScreenAction<SettingsMenu>>,
        makeComponent<MenuItem, StaticText<TEXT_LOCKVEHICLE>, SwitchScreenAction<Lockscreen>, StaticMenuItemIcon<&icons::lock>>,
        makeComponent<MenuItem, StaticText<TEXT_DEMOS>,       SwitchScreenAction<DemosMenu>>,
        makeComponent<MenuItem, StaticText<TEXT_POWEROFF>,    SwitchScreenAction<PoweroffDisplay>>,
        makeComponent<MenuItem, StaticText<TEXT_DEBUG>,       SwitchScreenAction<DebugMenu>>
    >
{};
};
