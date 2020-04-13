#pragma once

#include "menudisplay.h"
#include "staticmenudefinition.h"
#include "menuitem.h"
#include "actions/switchscreenaction.h"
#include "icons/back.h"
#include "texts.h"

namespace {
class DefaultModeSettingsMenu;
class TempomatModeSettingsMenu;
class LarsmModeSettingsMenu;
class BluetoothModeSettingsMenu;
class WebsocketModeSettingsMenu;
class SettingsMenu;
}

namespace {
class ModesSettingsMenu :
    public MenuDisplay,
    public StaticText<TEXT_MODESSETTINGS>,
    public StaticMenuDefinition<
        makeComponent<MenuItem, StaticText<TEXT_DEFAULTMODESETTIGNS>,   SwitchScreenAction<DefaultModeSettingsMenu>>,
        makeComponent<MenuItem, StaticText<TEXT_TEMPOMATMODESETTINGS>,  SwitchScreenAction<TempomatModeSettingsMenu>>,
        makeComponent<MenuItem, StaticText<TEXT_LARSMMODESETTINGS>,     SwitchScreenAction<LarsmModeSettingsMenu>>,
        makeComponent<MenuItem, StaticText<TEXT_BLUETOOTHMODESETTINGS>, SwitchScreenAction<BluetoothModeSettingsMenu>>,
        makeComponent<MenuItem, StaticText<TEXT_WEBSOCKETMODESETTINGS>, SwitchScreenAction<WebsocketModeSettingsMenu>>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,                  SwitchScreenAction<SettingsMenu>, StaticMenuItemIcon<&icons::back>>
    >
{};
}
