#pragma once

#include "menudisplay.h"
#include "staticmenudefinition.h"
#include "utils.h"
#include "actions/toggleboolaction.h"
#include "actions/switchscreenaction.h"
#include "checkboxicon.h"
#include "icons/back.h"
#include "texts.h"
#include "globals.h"

#include "displays/menus/commonsettingsmenu.h"
#include "displays/menus/wifisettingsmenu.h"
#include "displays/menus/bluetoothsettingsmenu.h"
#include "displays/menus/modessettingsmenu.h"
#include "displays/menus/potisettingsmenu.h"
#include "displays/menus/buzzermenu.h"
#include "displays/versiondisplay.h"

namespace {
struct FrontLedAccessor : public RefAccessor<bool> { bool &getRef() const override { return front.command.led; } };
struct BackLedAccessor : public RefAccessor<bool> { bool &getRef() const override { return back.command.led; } };

template<typename Tscreen>
class SettingsMenu :
    public MenuDisplay,
    public StaticText<TEXT_SETTINGS>,
    public StaticMenuDefinition<
        makeComponent<MenuItem, StaticText<TEXT_COMMONSETTINGS>,    SwitchScreenAction<CommonSettingsMenu<SettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_WIFISETTINGS>,      SwitchScreenAction<WifiSettingsMenu<SettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_BLUETOOTHSETTINGS>, SwitchScreenAction<BluetoothSettingsMenu<SettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_MODESSETTINGS>,     SwitchScreenAction<ModesSettingsMenu<SettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_POTISETTINGS>,      SwitchScreenAction<PotiSettingsMenu<SettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_BUZZER>,            SwitchScreenAction<BuzzerMenu<SettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_SETFRONTLED>,       ToggleBoolAction, CheckboxIcon, FrontLedAccessor>,
        makeComponent<MenuItem, StaticText<TEXT_SETBACKLED>,        ToggleBoolAction, CheckboxIcon, BackLedAccessor>,
        makeComponent<MenuItem, StaticText<TEXT_VERSION>,           SwitchScreenAction<VersionDisplay<SettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,              SwitchScreenAction<Tscreen>, StaticMenuItemIcon<&icons::back>>
    >
{};
}
