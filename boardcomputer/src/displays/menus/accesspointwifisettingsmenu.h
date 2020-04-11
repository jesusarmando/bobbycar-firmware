#pragma once

#include "staticmenudisplay.h"
#include "menuitems/staticswitchscreenmenuitem.h"
#include "texts.h"

namespace {
template<typename Tscreen>
class AccessPointWifiSettingsMenu final :
    public StaticTitle<TEXT_ACCESSPOINTWIFISETTINGS>,
    public StaticMenuDisplay<
        StaticSwitchScreenMenuItem<Tscreen, TEXT_BACK>
    >
{};
}
