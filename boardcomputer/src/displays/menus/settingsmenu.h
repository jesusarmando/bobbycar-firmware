#pragma once

#include <array>

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"
#include "texts.h"

namespace {
class CommonSettingsMenu;
class DefaultModeSettingsMenu;
class ManualModeSettingsMenu;
class BluetoothModeSettingsMenu;
class PotiSettingsMenu;
class MainMenu;
}

namespace {
class SettingsMenu final : public MenuDisplay<
    TEXT_SETTINGS,
    SwitchScreenMenuItem<CommonSettingsMenu, TEXT_COMMONSETTINGS>,
    SwitchScreenMenuItem<DefaultModeSettingsMenu, TEXT_DEFAULTMODESETTIGNS>,
    SwitchScreenMenuItem<ManualModeSettingsMenu, TEXT_MANUALMODESETTINGS>,
    SwitchScreenMenuItem<BluetoothModeSettingsMenu, TEXT_BLUETOOTHMODESETTINGS>,
    SwitchScreenMenuItem<PotiSettingsMenu,TEXT_POTISETTINGS>,
    SwitchScreenMenuItem<MainMenu, TEXT_BACK>
>
{};
}
