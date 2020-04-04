#pragma once

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"
#include "displays/bluetoothstatusdisplay.h"
#include "texts.h"

namespace {
template<typename Tscreen>
class BluetoothModeSettingsMenu final : public MenuDisplay<
    TEXT_BLUETOOTHMODESETTINGS,
    SwitchScreenMenuItem<BluetoothStatusDisplay<BluetoothModeSettingsMenu<Tscreen>>, TEXT_BLUETOOTHSTATUS>,
    SwitchScreenMenuItem<Tscreen, TEXT_BACK>
>
{};
}
