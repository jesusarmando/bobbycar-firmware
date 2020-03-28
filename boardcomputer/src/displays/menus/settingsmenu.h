#pragma once

#include <array>

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"
#include "displays/menus/commonsettingsmenu.h"
#include "displays/menus/defaultmodesettingsmenu.h"
#include "displays/menus/manualmodesettingsmenu.h"
#include "displays/menus/bluetoothmodesettingsmenu.h"
#include "displays/menus/potisettingsmenu.h"
#include "texts.h"

namespace {
template<typename Tscreen>
class SettingsMenu final : public MenuDisplay<
    TEXT_SETTINGS,
    SwitchScreenMenuItem<CommonSettingsMenu<SettingsMenu<Tscreen>>, TEXT_COMMONSETTINGS>,
    SwitchScreenMenuItem<DefaultModeSettingsMenu<SettingsMenu<Tscreen>>, TEXT_DEFAULTMODESETTIGNS>,
    SwitchScreenMenuItem<ManualModeSettingsMenu<SettingsMenu<Tscreen>>, TEXT_MANUALMODESETTINGS>,
    SwitchScreenMenuItem<BluetoothModeSettingsMenu<SettingsMenu<Tscreen>>, TEXT_BLUETOOTHMODESETTINGS>,
    SwitchScreenMenuItem<PotiSettingsMenu<SettingsMenu<Tscreen>>,TEXT_POTISETTINGS>,
    SwitchScreenMenuItem<Tscreen, TEXT_BACK>
>
{};
}
