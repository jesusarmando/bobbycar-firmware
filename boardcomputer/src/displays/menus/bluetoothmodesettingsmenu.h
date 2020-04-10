#pragma once

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"
#include "texts.h"

namespace {
template<typename Tscreen>
class BluetoothModeSettingsMenu final : public MenuDisplay<
    TEXT_BLUETOOTHMODESETTINGS,
    SwitchScreenMenuItem<Tscreen, TEXT_BACK>
>
{};
}
