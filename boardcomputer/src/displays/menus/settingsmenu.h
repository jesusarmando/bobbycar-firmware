#pragma once

#include "menudisplay.h"
#include "menuitems/switchscreenmenuitem.h"
#include "displays/menus/commonsettingsmenu.h"
#include "displays/menus/defaultmodesettingsmenu.h"
#include "displays/menus/tempomatmodesettingsmenu.h"
#include "displays/menus/bluetoothmodesettingsmenu.h"
#include "displays/menus/potisettingsmenu.h"
#include "menuitems/rebootmenuitem.h"
#include "displays/versiondisplay.h"
#include "texts.h"

namespace {
template<typename Tscreen>
class SettingsMenu final : public MenuDisplay<
    TEXT_SETTINGS,
    SwitchScreenMenuItem<CommonSettingsMenu<SettingsMenu<Tscreen>>, TEXT_COMMONSETTINGS>,
    SwitchScreenMenuItem<DefaultModeSettingsMenu<SettingsMenu<Tscreen>>, TEXT_DEFAULTMODESETTIGNS>,
    SwitchScreenMenuItem<TempomatModeSettingsMenu<SettingsMenu<Tscreen>>, TEXT_TEMPOMATMODESETTINGS>,
    SwitchScreenMenuItem<BluetoothModeSettingsMenu<SettingsMenu<Tscreen>>, TEXT_BLUETOOTHMODESETTINGS>,
    SwitchScreenMenuItem<PotiSettingsMenu<SettingsMenu<Tscreen>>, TEXT_POTISETTINGS>,
    RebootMenuItem<TEXT_REBOOT>,
    SwitchScreenMenuItem<VersionDisplay<SettingsMenu<Tscreen>>, TEXT_VERSION>,
    SwitchScreenMenuItem<Tscreen, TEXT_BACK>
>
{};
}
