#pragma once

#include <HardwareSerial.h>

#include "menudisplay.h"
#include "staticmenudefinition.h"
#include "utils.h"
#include "actions/toggleboolaction.h"
#include "actions/switchscreenaction.h"
#include "checkboxicon.h"
#include "icons/wifi.h"
#include "icons/bluetooth.h"
#include "icons/back.h"
#include "texts.h"
#include "globals.h"

namespace {
class LimitsSettingsMenu;
class WifiSettingsMenu;
class BluetoothSettingsMenu;
class ModesSettingsMenu;
class HardwareSettingsMenu;
class BuzzerMenu;
class AboutMenu;
class MainMenu;
}

namespace {
struct FrontLedAccessor : public RefAccessor<bool> { bool &getRef() const override { return front.command.led; } };
struct BackLedAccessor : public RefAccessor<bool> { bool &getRef() const override { return back.command.led; } };

class SettingsMenu :
    public MenuDisplay,
    public StaticText<TEXT_SETTINGS>,
    public StaticMenuDefinition<
        makeComponent<MenuItem, StaticText<TEXT_LIMITSSETTINGS>,    SwitchScreenAction<LimitsSettingsMenu>>,
        makeComponent<MenuItem, StaticText<TEXT_WIFISETTINGS>,      SwitchScreenAction<WifiSettingsMenu>, StaticMenuItemIcon<&icons::wifi>>,
        makeComponent<MenuItem, StaticText<TEXT_BLUETOOTHSETTINGS>, SwitchScreenAction<BluetoothSettingsMenu>, StaticMenuItemIcon<&icons::bluetooth>>,
        makeComponent<MenuItem, StaticText<TEXT_MODESSETTINGS>,     SwitchScreenAction<ModesSettingsMenu>>,
        makeComponent<MenuItem, StaticText<TEXT_HARDWARESETTINGS>,  SwitchScreenAction<HardwareSettingsMenu>>,
        makeComponent<MenuItem, StaticText<TEXT_BUZZER>,            SwitchScreenAction<BuzzerMenu>>,
        makeComponent<MenuItem, StaticText<TEXT_SETFRONTLED>,       ToggleBoolAction, CheckboxIcon, FrontLedAccessor>,
        makeComponent<MenuItem, StaticText<TEXT_SETBACKLED>,        ToggleBoolAction, CheckboxIcon, BackLedAccessor>,
        makeComponent<MenuItem, StaticText<TEXT_ABOUT>,             SwitchScreenAction<AboutMenu>>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,              SwitchScreenAction<MainMenu>, StaticMenuItemIcon<&icons::back>>
    >
{};
}
