#pragma once

#include "staticmenudisplay.h"
#include "menuitems/staticswitchscreenmenuitem.h"
#include "texts.h"

namespace {
template<typename Tscreen>
class BluetoothModeSettingsMenu final :
    public StaticTitle<TEXT_BLUETOOTHMODESETTINGS>,
    public StaticMenuDisplay<
        StaticSwitchScreenMenuItem<Tscreen, TEXT_BACK>
    >
{};
}
