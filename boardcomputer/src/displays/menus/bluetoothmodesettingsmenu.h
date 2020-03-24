#pragma once

#include <array>

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"
#include "texts.h"

namespace {
class SettingsMenu;
}

namespace {
class BluetoothModeSettingsMenu final : public MenuDisplay<
    TEXT_BLUETOOTHMODESETTINGS,
    SwitchScreenMenuItem<SettingsMenu, TEXT_BACK>
>
{};
}
