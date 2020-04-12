#pragma once

#include "menudisplay.h"
#include "staticmenudefinition.h"
#include "menuitem.h"
#include "actions/switchscreenaction.h"
#include "icons/back.h"
#include "texts.h"

#include "displays/menus/defaultmodesettingsmenu.h"
#include "displays/menus/tempomatmodesettingsmenu.h"
#include "displays/menus/larsmmodesettingsmenu.h"
#include "displays/menus/bluetoothmodesettingsmenu.h"
#include "displays/menus/websocketmodesettingsmenu.h"

namespace {
template<typename Tscreen>
class ModesSettingsMenu :
    public MenuDisplay,
    public StaticText<TEXT_MODESSETTINGS>,
    public StaticMenuDefinition<
        makeComponent<MenuItem, StaticText<TEXT_DEFAULTMODESETTIGNS>,   SwitchScreenAction<DefaultModeSettingsMenu<ModesSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_TEMPOMATMODESETTINGS>,  SwitchScreenAction<TempomatModeSettingsMenu<ModesSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_LARSMMODESETTINGS>,     SwitchScreenAction<LarsmModeSettingsMenu<ModesSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_BLUETOOTHMODESETTINGS>, SwitchScreenAction<BluetoothModeSettingsMenu<ModesSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_WEBSOCKETMODESETTINGS>, SwitchScreenAction<WebsocketModeSettingsMenu<ModesSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,                  SwitchScreenAction<Tscreen>, StaticMenuItemIcon<&icons::back>>
    >
{};
}
