#pragma once

#include "staticmenudisplay.h"
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
    public StaticText<TEXT_WIFISETTINGS>,
    public StaticMenuDisplay<
        makeComponent<MenuItem, StaticText<TEXT_GENERICWIFISETTINGS>,     DefaultFont,  DefaultColor, SwitchScreenAction<GenericWifiSettingsMenu<WifiSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_STATIONWIFISETTINGS>,     DefaultFont,  DefaultColor, SwitchScreenAction<StationWifiSettingsMenu<WifiSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_WIFISCAN>,                DefaultFont,  DefaultColor, SwitchScreenAction<WifiScanMenu<WifiSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_ACCESSPOINTWIFISETTINGS>, DefaultFont,  DefaultColor, SwitchScreenAction<AccessPointWifiSettingsMenu<WifiSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,                    DefaultFont,  DefaultColor, SwitchScreenAction<Tscreen>, StaticMenuItemIcon<&icons::back>>
    >
{};
}
