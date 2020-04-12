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
        makeComponent<MenuItem, StaticText<TEXT_DEFAULTMODESETTIGNS>,   DefaultFont, DefaultColor, SwitchScreenAction<DefaultModeSettingsMenu<ModesSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_TEMPOMATMODESETTINGS>,  DefaultFont, DefaultColor, SwitchScreenAction<TempomatModeSettingsMenu<ModesSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_LARSMMODESETTINGS>,     DefaultFont, DefaultColor, SwitchScreenAction<LarsmModeSettingsMenu<ModesSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_BLUETOOTHMODESETTINGS>, DefaultFont, DefaultColor, SwitchScreenAction<BluetoothModeSettingsMenu<ModesSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_WEBSOCKETMODESETTINGS>, DefaultFont, DefaultColor, SwitchScreenAction<WebsocketModeSettingsMenu<ModesSettingsMenu<Tscreen>>>>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,                  DefaultFont, DefaultColor, SwitchScreenAction<Tscreen>, StaticMenuItemIcon<&icons::back>>
    >
{};
}
