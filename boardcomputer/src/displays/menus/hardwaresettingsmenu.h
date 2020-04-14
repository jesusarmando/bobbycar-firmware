#pragma once

#include "menudisplay.h"
#include "staticmenudefinition.h"
#include "utils.h"
#include "actions/toggleboolaction.h"
#include "actions/switchscreenaction.h"
#include "checkboxicon.h"
#include "icons/back.h"
#include "texts.h"
#include "globals.h"
#include "settingsaccessors.h"

namespace {
class PotiSettingsMenu;
class EnableMenu;
class InvertMenu;
class SettingsMenu;
}

namespace {
class HardwareSettingsMenu :
    public MenuDisplay,
    public StaticText<TEXT_HARDWARESETTINGS>,
    public StaticMenuDefinition<
        makeComponent<MenuItem, StaticText<TEXT_SETENABLED>,    SwitchScreenAction<EnableMenu>>,
        makeComponent<MenuItem, StaticText<TEXT_SETINVERTED>,   SwitchScreenAction<InvertMenu>>,
        makeComponent<MenuItem, StaticText<TEXT_POTISETTINGS>,  SwitchScreenAction<PotiSettingsMenu>>,
        makeComponent<MenuItem, StaticText<TEXT_SWAPFRONTBACK>, ToggleBoolAction, CheckboxIcon, SwapFrontBackAccessor>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,          SwitchScreenAction<SettingsMenu>, StaticMenuItemIcon<&icons::back>>
    >
{};
}
