#pragma once

#include "menudisplay.h"
#include "staticmenudefinition.h"
#include "utils.h"
#include "actions/switchscreenaction.h"
#include "icons/back.h"
#include "texts.h"

#include "displays/menus/genericwifisettingsmenu.h"
#include "displays/menus/stationwifisettingsmenu.h"
#include "displays/menus/wifiscanmenu.h"
#include "displays/menus/accesspointwifisettingsmenu.h"

namespace {
template<typename Tscreen>
class WifiSettingsMenu :
    public MenuDisplay,
    public StaticText<TEXT_WIFISETTINGS>,
    public StaticMenuDefinition<
        makeComponent<MenuItem, StaticText<TEXT_GENERICWIFISETTINGS>,     SwitchScreenAction<GenericWifiSettingsMenu<WifiSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_STATIONWIFISETTINGS>,     SwitchScreenAction<StationWifiSettingsMenu<WifiSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_WIFISCAN>,                SwitchScreenAction<WifiScanMenu<WifiSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_ACCESSPOINTWIFISETTINGS>, SwitchScreenAction<AccessPointWifiSettingsMenu<WifiSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,                    SwitchScreenAction<Tscreen>, StaticMenuItemIcon<&icons::back>>
    >
{};
}
