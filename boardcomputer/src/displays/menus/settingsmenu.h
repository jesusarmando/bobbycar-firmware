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

namespace {
class CommonSettingsMenu;
class WifiSettingsMenu;
class BluetoothSettingsMenu;
class ModesSettingsMenu;
class PotiSettingsMenu;
class BuzzerMenu;
class VersionDisplay;
class MainMenu;
}

namespace {
struct FrontLedAccessor : public RefAccessor<bool> { bool &getRef() const override { return front.command.led; } };
struct BackLedAccessor : public RefAccessor<bool> { bool &getRef() const override { return back.command.led; } };

class SettingsMenu :
    public MenuDisplay,
    public StaticText<TEXT_SETTINGS>,
    public StaticMenuDefinition<
        makeComponent<MenuItem, StaticText<TEXT_COMMONSETTINGS>,    SwitchScreenAction<CommonSettingsMenu>>,
        makeComponent<MenuItem, StaticText<TEXT_WIFISETTINGS>,      SwitchScreenAction<WifiSettingsMenu>>,
        makeComponent<MenuItem, StaticText<TEXT_BLUETOOTHSETTINGS>, SwitchScreenAction<BluetoothSettingsMenu>>,
        makeComponent<MenuItem, StaticText<TEXT_MODESSETTINGS>,     SwitchScreenAction<ModesSettingsMenu>>,
        makeComponent<MenuItem, StaticText<TEXT_POTISETTINGS>,      SwitchScreenAction<PotiSettingsMenu>>,
        makeComponent<MenuItem, StaticText<TEXT_BUZZER>,            SwitchScreenAction<BuzzerMenu>>,
        makeComponent<MenuItem, StaticText<TEXT_SETFRONTLED>,       ToggleBoolAction, CheckboxIcon, FrontLedAccessor>,
        makeComponent<MenuItem, StaticText<TEXT_SETBACKLED>,        ToggleBoolAction, CheckboxIcon, BackLedAccessor>,
        makeComponent<MenuItem, StaticText<TEXT_VERSION>,           SwitchScreenAction<VersionDisplay>>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,              SwitchScreenAction<MainMenu>, StaticMenuItemIcon<&icons::back>>
    >
{};
}
