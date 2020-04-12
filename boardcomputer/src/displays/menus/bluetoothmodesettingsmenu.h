#pragma once

#include "staticmenudisplay.h"
#include "menuitems/backmenuitem.h"
#include "texts.h"

namespace {
template<typename Tscreen>
class BluetoothModeSettingsMenu final :
    public StaticTitle<TEXT_BLUETOOTHMODESETTINGS>,
    public StaticMenuDisplay<
        BackMenuItem<Tscreen>
    >
{};
}
