#pragma once

#include "menudisplay.h"
#include "staticmenudefinition.h"
#include "menuitem.h"
#include "actions/switchscreenaction.h"
#include "icons/back.h"
#include "texts.h"

namespace {
template<typename Tscreen>
class BluetoothModeSettingsMenu :
    public MenuDisplay,
    public StaticText<TEXT_BLUETOOTHMODESETTINGS>,
    public StaticMenuDefinition<
        makeComponent<MenuItem, StaticText<TEXT_BACK>, SwitchScreenAction<Tscreen>, StaticMenuItemIcon<&icons::back>>
    >
{};
}
