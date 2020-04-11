#pragma once

#include "staticmenudisplay.h"
#include "menuitems/staticswitchscreenmenuitem.h"
#include "displays/menus/genericwifisettingsmenu.h"
#include "displays/menus/stationwifisettingsmenu.h"
#include "displays/menus/wifiscanmenu.h"
#include "displays/menus/accesspointwifisettingsmenu.h"
#include "texts.h"

namespace {
template<typename Tscreen>
class WifiSettingsMenu final :
    public StaticTitle<TEXT_WIFISETTINGS>,
    public StaticMenuDisplay<
        StaticSwitchScreenMenuItem<GenericWifiSettingsMenu<WifiSettingsMenu<Tscreen>>, TEXT_GENERICWIFISETTINGS>,
        StaticSwitchScreenMenuItem<StationWifiSettingsMenu<WifiSettingsMenu<Tscreen>>, TEXT_STATIONWIFISETTINGS>,
        StaticSwitchScreenMenuItem<WifiScanMenu<WifiSettingsMenu<Tscreen>>, TEXT_WIFISCAN>,
        StaticSwitchScreenMenuItem<AccessPointWifiSettingsMenu<WifiSettingsMenu<Tscreen>>, TEXT_ACCESSPOINTWIFISETTINGS>,
        StaticSwitchScreenMenuItem<Tscreen, TEXT_BACK>
    >
{};
}
