#pragma once

#include "staticmenudisplay.h"
#include "menuitems/staticswitchscreenmenuitem.h"
#include "displays/menus/wifiscanmenu.h"
#include "texts.h"

namespace {
template<typename Tscreen>
class WifiSettingsMenu final :
    public StaticTitle<TEXT_WIFISETTINGS>,
    public StaticMenuDisplay<
        StaticSwitchScreenMenuItem<WifiScanMenu<WifiSettingsMenu<Tscreen>>, TEXT_WIFISCAN>,
        StaticSwitchScreenMenuItem<Tscreen, TEXT_BACK>
    >
{};
}
