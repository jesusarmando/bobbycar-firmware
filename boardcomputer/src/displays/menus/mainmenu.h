#pragma once

#include "menudisplay.h"
#include "staticmenudefinition.h"
#include "menuitem.h"
#include "actions/switchscreenaction.h"
#include "actions/rebootaction.h"
#include "texts.h"
#include "icons/back.h"
#include "icons/modes.h"
#include "icons/presets.h"
#include "icons/graph.h"
#include "icons/settings.h"
#include "icons/lock.h"
#include "icons/demos.h"
#include "icons/poweroff.h"
#include "icons/reboot.h"

namespace {
class StatusDisplay;
class SelectModeMenu;
class PresetsMenu;
class GraphsMenu;
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
        makeComponent<MenuItem, StaticText<TEXT_SELECTMODE>,  SwitchScreenAction<SelectModeMenu>, StaticMenuItemIcon<&icons::modes>>,
        makeComponent<MenuItem, StaticText<TEXT_PRESETS>,     SwitchScreenAction<PresetsMenu>, StaticMenuItemIcon<&icons::presets>>,
        makeComponent<MenuItem, StaticText<TEXT_GRAPHS>,      SwitchScreenAction<GraphsMenu>, StaticMenuItemIcon<&icons::graph>>,
        makeComponent<MenuItem, StaticText<TEXT_SETTINGS>,    SwitchScreenAction<SettingsMenu>, StaticMenuItemIcon<&icons::settings>>,
        makeComponent<MenuItem, StaticText<TEXT_LOCKVEHICLE>, SwitchScreenAction<Lockscreen>, StaticMenuItemIcon<&icons::lock>>,
        makeComponent<MenuItem, StaticText<TEXT_DEMOS>,       SwitchScreenAction<DemosMenu>, StaticMenuItemIcon<&icons::demos>>,
        makeComponent<MenuItem, StaticText<TEXT_POWEROFF>,    SwitchScreenAction<PoweroffDisplay>, StaticMenuItemIcon<&icons::poweroff>>,
        makeComponent<MenuItem, StaticText<TEXT_REBOOT>,      RebootAction, StaticMenuItemIcon<&icons::reboot>>,
        makeComponent<MenuItem, StaticText<TEXT_DEBUG>,       SwitchScreenAction<DebugMenu>>
    >
{};
};
