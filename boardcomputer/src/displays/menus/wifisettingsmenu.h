#pragma once

#include "menudisplay.h"
#include "staticmenudefinition.h"
#include "utils.h"
#include "actions/switchscreenaction.h"
#include "icons/back.h"
#include "texts.h"

namespace {
class GenericWifiSettingsMenu;
class StationWifiSettingsMenu;
class WifiScanMenu;
class AccessPointWifiSettingsMenu;
class SettingsMenu;
}

namespace {
class WifiSettingsMenu :
    public MenuDisplay,
    public StaticText<TEXT_WIFISETTINGS>,
    public StaticMenuDefinition<
        makeComponent<MenuItem, StaticText<TEXT_GENERICWIFISETTINGS>,     SwitchScreenAction<GenericWifiSettingsMenu>>,
        makeComponent<MenuItem, StaticText<TEXT_STATIONWIFISETTINGS>,     SwitchScreenAction<StationWifiSettingsMenu>>,
        makeComponent<MenuItem, StaticText<TEXT_WIFISCAN>,                SwitchScreenAction<WifiScanMenu>>,
        makeComponent<MenuItem, StaticText<TEXT_ACCESSPOINTWIFISETTINGS>, SwitchScreenAction<AccessPointWifiSettingsMenu>>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,                    SwitchScreenAction<SettingsMenu>, StaticMenuItemIcon<&icons::back>>
    >
{};
}
