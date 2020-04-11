#pragma once

#include "staticmenudisplay.h"
#include "menuitems/staticswitchscreenmenuitem.h"
#include "displays/menus/defaultmodesettingsmenu.h"
#include "displays/menus/tempomatmodesettingsmenu.h"
#include "displays/menus/bluetoothmodesettingsmenu.h"
#include "displays/menus/websocketmodesettingsmenu.h"
#include "texts.h"

namespace {
template<typename Tscreen>
class ModesSettingsMenu final :
    public StaticTitle<TEXT_MODESSETTINGS>,
    public StaticMenuDisplay<
        StaticSwitchScreenMenuItem<DefaultModeSettingsMenu<ModesSettingsMenu<Tscreen>>, TEXT_DEFAULTMODESETTIGNS>,
        StaticSwitchScreenMenuItem<TempomatModeSettingsMenu<ModesSettingsMenu<Tscreen>>, TEXT_TEMPOMATMODESETTINGS>,
        StaticSwitchScreenMenuItem<BluetoothModeSettingsMenu<ModesSettingsMenu<Tscreen>>, TEXT_BLUETOOTHMODESETTINGS>,
        StaticSwitchScreenMenuItem<WebsocketModeSettingsMenu<ModesSettingsMenu<Tscreen>>, TEXT_WEBSOCKETMODESETTINGS>,
        StaticSwitchScreenMenuItem<Tscreen, TEXT_BACK>
    >
{};
}
