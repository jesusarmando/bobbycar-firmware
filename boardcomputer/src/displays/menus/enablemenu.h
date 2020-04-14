#pragma once

#include "menudisplay.h"
#include "staticmenudefinition.h"
#include "utils.h"
#include "menuitem.h"
#include "actions/toggleboolaction.h"
#include "actions/switchscreenaction.h"
#include "checkboxicon.h"
#include "icons/back.h"
#include "texts.h"
#include "settingsaccessors.h"

namespace {
class HardwareSettingsMenu;
}

namespace {
class EnableMenu :
    public MenuDisplay,
    public StaticText<TEXT_SETENABLED>,
    public StaticMenuDefinition<
        makeComponent<MenuItem, StaticText<TEXT_ENABLEFRONTLEFT>,  ToggleBoolAction, CheckboxIcon, FrontLeftEnabledAccessor>,
        makeComponent<MenuItem, StaticText<TEXT_ENABLEFRONTRIGHT>, ToggleBoolAction, CheckboxIcon, FrontRightEnabledAccessor>,
        makeComponent<MenuItem, StaticText<TEXT_ENABLEBACKLEFT>,   ToggleBoolAction, CheckboxIcon, BackLeftEnabledAccessor>,
        makeComponent<MenuItem, StaticText<TEXT_ENABLEBACKRIGHT>,  ToggleBoolAction, CheckboxIcon, BackRightEnabledAccessor>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,             SwitchScreenAction<HardwareSettingsMenu>, StaticMenuItemIcon<&icons::back>>
    >
{};
}
