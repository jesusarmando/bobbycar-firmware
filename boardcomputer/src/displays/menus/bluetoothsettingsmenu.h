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
        makeComponent<MenuItem, BluetoothAvailableText,                 DefaultFont, DisabledColor, DummyAction>,
        makeComponent<MenuItem, BluetoothHasClientText,                 DefaultFont, DisabledColor, DummyAction>,
//        makeComponent<MenuItem, BluetoothConnectedText,                 DefaultFont, DisabledColor, DummyAction>, // crashes
        makeComponent<MenuItem, BluetoothIsReadyText,                   DefaultFont, DisabledColor, DummyAction>,
        makeComponent<MenuItem, BluetoothIsReadyMasterText,             DefaultFont, DisabledColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_BLUETOOTHBEGIN>,        DefaultFont, DisabledColor, BluetoothBeginAction>,
        makeComponent<MenuItem, StaticText<TEXT_BLUETOOTHBEGINMASTER>,  DefaultFont, DisabledColor, BluetoothBeginMasterAction>,
        makeComponent<MenuItem, StaticText<TEXT_BLUETOOTHFLUSH>,        DefaultFont, DisabledColor, BluetoothFlushAction>,
        makeComponent<MenuItem, StaticText<TEXT_BLUETOOTHEND>,          DefaultFont, DisabledColor, BluetoothEndAction>,
        makeComponent<MenuItem, StaticText<TEXT_BLUETOOTHDISCONNECT>,   DefaultFont, DisabledColor, BluetoothDisconnectAction>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,                  DefaultFont, DefaultColor,  SwitchScreenAction<Tscreen>, StaticMenuItemIcon<&icons::back>>
    >
{};
}
