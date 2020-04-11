#pragma once

#include "staticmenudisplay.h"
#include "menuitems/staticswitchscreenmenuitem.h"
#include "texts.h"

namespace {
template<typename Tscreen>
class StationWifiSettingsMenu final :
    public StaticTitle<TEXT_STATIONWIFISETTINGS>,
    public StaticMenuDisplay<
        StaticSwitchScreenMenuItem<Tscreen, TEXT_BACK>
    >
{};
}
