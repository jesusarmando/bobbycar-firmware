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

template<typename Tscreen>
class BluetoothSettingsMenu :
    public MenuDisplay,
    public StaticText<TEXT_BLUETOOTHSETTINGS>,
    public StaticMenuDefinition<
        makeComponent<MenuItem, BluetoothAvailableText,                 DisabledColor, DummyAction>,
        makeComponent<MenuItem, BluetoothHasClientText,                 DisabledColor, DummyAction>,
//        makeComponent<MenuItem, BluetoothConnectedText,                 DisabledColor, DummyAction>, // crashes
        makeComponent<MenuItem, BluetoothIsReadyText,                   DisabledColor, DummyAction>,
        makeComponent<MenuItem, BluetoothIsReadyMasterText,             DisabledColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_BLUETOOTHBEGIN>,        DisabledColor, BluetoothBeginAction>,
        makeComponent<MenuItem, StaticText<TEXT_BLUETOOTHBEGINMASTER>,  DisabledColor, BluetoothBeginMasterAction>,
        makeComponent<MenuItem, StaticText<TEXT_BLUETOOTHFLUSH>,        DisabledColor, BluetoothFlushAction>,
        makeComponent<MenuItem, StaticText<TEXT_BLUETOOTHEND>,          DisabledColor, BluetoothEndAction>,
        makeComponent<MenuItem, StaticText<TEXT_BLUETOOTHDISCONNECT>,   DisabledColor, BluetoothDisconnectAction>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,                  SwitchScreenAction<Tscreen>, StaticMenuItemIcon<&icons::back>>
    >
{};
}
