#pragma once

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"
#include "displays/bluetoothstatusdisplay.h"
#include "texts.h"

namespace {
template<typename Tscreen>
class BluetoothSettingsMenu final : public MenuDisplay<
    TEXT_BLUETOOTHSETTINGS,
    SwitchScreenMenuItem<BluetoothStatusDisplay<BluetoothSettingsMenu<Tscreen>>, TEXT_BLUETOOTHSTATUS>,
    SwitchScreenMenuItem<Tscreen, TEXT_BACK>
>
{};
}
