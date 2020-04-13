#pragma once

#include "menudisplay.h"
#include "staticmenudefinition.h"
#include "menuitem.h"
#include "actions/dummyaction.h"
#include "actions/bluetoothbeginaction.h"
#include "actions/bluetoothbeginmasteraction.h"
#include "actions/bluetoothflushaction.h"
#include "actions/bluetoothendaction.h"
#include "actions/bluetoothdisconnectaction.h"
#include "actions/switchscreenaction.h"
#include "bluetoothtexthelpers.h"
#include "icons/back.h"
#include "texts.h"

namespace {
class SettingsMenu;
}

namespace {
class BluetoothSettingsMenu :
    public MenuDisplay,
    public StaticText<TEXT_BLUETOOTHSETTINGS>,
    public StaticMenuDefinition<
        makeComponent<MenuItem, BluetoothAvailableText,                 DisabledColor, StaticFont<2>, DummyAction>,
        makeComponent<MenuItem, BluetoothHasClientText,                 DisabledColor, StaticFont<2>, DummyAction>,
//        makeComponent<MenuItem, BluetoothConnectedText,                 DisabledColor, StaticFont<2>, DummyAction>, // crashes
        makeComponent<MenuItem, BluetoothIsReadyText,                   DisabledColor, StaticFont<2>, DummyAction>,
        makeComponent<MenuItem, BluetoothIsReadyMasterText,             DisabledColor, StaticFont<2>, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_BLUETOOTHBEGIN>,        BluetoothBeginAction>,
        makeComponent<MenuItem, StaticText<TEXT_BLUETOOTHBEGINMASTER>,  BluetoothBeginMasterAction>,
        makeComponent<MenuItem, StaticText<TEXT_BLUETOOTHFLUSH>,        BluetoothFlushAction>,
        makeComponent<MenuItem, StaticText<TEXT_BLUETOOTHEND>,          BluetoothEndAction>,
        makeComponent<MenuItem, StaticText<TEXT_BLUETOOTHDISCONNECT>,   BluetoothDisconnectAction>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,                  SwitchScreenAction<SettingsMenu>, StaticMenuItemIcon<&icons::back>>
    >
{};
}
