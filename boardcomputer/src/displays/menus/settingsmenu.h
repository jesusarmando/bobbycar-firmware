#pragma once

#include "staticmenudisplay.h"
#include "utils.h"
#include "actions/switchscreenaction.h"
#include "actions/rebootaction.h"
#include "icons/back.h"
#include "texts.h"

#include "displays/menus/commonsettingsmenu.h"
#include "displays/menus/wifisettingsmenu.h"
#include "displays/menus/bluetoothsettingsmenu.h"
#include "displays/menus/modessettingsmenu.h"
#include "displays/menus/potisettingsmenu.h"
#include "displays/versiondisplay.h"

namespace {
template<typename Tscreen>
class SettingsMenu :
    public StaticText<TEXT_SETTINGS>,
    public StaticMenuDisplay<
        makeComponent<MenuItem, StaticText<TEXT_COMMONSETTINGS>,    DefaultFont, DefaultColor, SwitchScreenAction<CommonSettingsMenu<SettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_WIFISETTINGS>,      DefaultFont, DefaultColor, SwitchScreenAction<WifiSettingsMenu<SettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_BLUETOOTHSETTINGS>, DefaultFont, DefaultColor, SwitchScreenAction<BluetoothSettingsMenu<SettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_MODESSETTINGS>,     DefaultFont, DefaultColor, SwitchScreenAction<ModesSettingsMenu<SettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_POTISETTINGS>,      DefaultFont, DefaultColor, SwitchScreenAction<PotiSettingsMenu<SettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_REBOOT>,            DefaultFont, DefaultColor, RebootAction>,
        makeComponent<MenuItem, StaticText<TEXT_VERSION>,           DefaultFont, DefaultColor, SwitchScreenAction<VersionDisplay<SettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,              DefaultFont, DefaultColor, SwitchScreenAction<Tscreen>, StaticMenuItemIcon<&icons::back>>
    >
{};
}
