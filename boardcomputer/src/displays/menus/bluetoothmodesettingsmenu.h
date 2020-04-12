#pragma once

#include "staticmenudisplay.h"
#include "menuitem.h"
#include "actions/switchscreenaction.h"
#include "texts.h"

namespace {
template<typename Tscreen>
class BluetoothModeSettingsMenu :
    public StaticText<TEXT_BLUETOOTHMODESETTINGS>,
    public StaticMenuDisplay<
        makeComponent<MenuItem, StaticText<TEXT_BACK>, DefaultFont, DefaultColor, SwitchScreenAction<Tscreen>>
    >
{};
}
