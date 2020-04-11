#pragma once

#include "staticmenudisplay.h"
#include "menuitems/staticswitchscreenmenuitem.h"
#include "displays/menus/commonsettingsmenu.h"
#include "displays/menus/wifisettingsmenu.h"
#include "displays/menus/bluetoothsettingsmenu.h"
#include "displays/menus/defaultmodesettingsmenu.h"
#include "displays/menus/tempomatmodesettingsmenu.h"
#include "displays/menus/bluetoothmodesettingsmenu.h"
#include "displays/menus/potisettingsmenu.h"
#include "menuitems/rebootmenuitem.h"
#include "displays/versiondisplay.h"
#include "texts.h"

namespace {
template<typename Tscreen>
class SettingsMenu final :
    public StaticTitle<TEXT_SETTINGS>,
    public StaticMenuDisplay<
        StaticSwitchScreenMenuItem<CommonSettingsMenu<SettingsMenu<Tscreen>>, TEXT_COMMONSETTINGS>,
        StaticSwitchScreenMenuItem<WifiSettingsMenu<SettingsMenu<Tscreen>>, TEXT_WIFISETTINGS>,
        StaticSwitchScreenMenuItem<BluetoothSettingsMenu<SettingsMenu<Tscreen>>, TEXT_BLUETOOTHSETTINGS>,
        StaticSwitchScreenMenuItem<DefaultModeSettingsMenu<SettingsMenu<Tscreen>>, TEXT_DEFAULTMODESETTIGNS>,
        StaticSwitchScreenMenuItem<TempomatModeSettingsMenu<SettingsMenu<Tscreen>>, TEXT_TEMPOMATMODESETTINGS>,
        StaticSwitchScreenMenuItem<BluetoothModeSettingsMenu<SettingsMenu<Tscreen>>, TEXT_BLUETOOTHMODESETTINGS>,
        StaticSwitchScreenMenuItem<PotiSettingsMenu<SettingsMenu<Tscreen>>, TEXT_POTISETTINGS>,
        RebootMenuItem<TEXT_REBOOT>,
        StaticSwitchScreenMenuItem<VersionDisplay<SettingsMenu<Tscreen>>, TEXT_VERSION>,
        StaticSwitchScreenMenuItem<Tscreen, TEXT_BACK>
    >
{};
}
