#pragma once

#include "staticmenudisplay.h"
#include "menuitem.h"
#include "actions/dummyaction.h"
#include "actions/bluetoothbeginaction.h"
#include "actions/bluetoothbeginmasteraction.h"
#include "actions/bluetoothflushaction.h"
#include "actions/bluetoothendaction.h"
#include "actions/bluetoothdisconnectaction.h"
#include "actions/switchscreenaction.h"
#include "texts.h"

namespace {
struct BluetoothAvailableText : public virtual TextInterface {
public:
    String text() const override { return String{"available: "} + bluetoothSerial.available(); }
};
struct BluetoothHasClientText : public virtual TextInterface {
public:
    String text() const override { return String{"hasClient: "} + (bluetoothSerial.hasClient() ? "true" : "false"); }
};
struct BluetoothConnectedText : public virtual TextInterface {
public:
    String text() const override { return String{"connected: "} + (bluetoothSerial.connected() ? "true" : "false"); }
};
struct BluetoothIsReadyText : public virtual TextInterface {
public:
    String text() const override { return String{"isReady: "} + (bluetoothSerial.isReady() ? "true" : "false"); }
};
struct BluetoothIsReadyMasterText : public virtual TextInterface {
public:
    String text() const override { return String{"isReady (M): "} + (bluetoothSerial.isReady(true) ? "true" : "false"); }
};

template<typename Tscreen>
class BluetoothSettingsMenu :
    public StaticText<TEXT_BLUETOOTHSETTINGS>,
    public StaticMenuDisplay<
        makeComponent<MenuItem, BluetoothAvailableText,                 DefaultFont, DisabledColor, DummyAction>,
        makeComponent<MenuItem, BluetoothHasClientText,                 DefaultFont, DisabledColor, DummyAction>,
//        makeComponent<MenuItem, BluetoothConnectedText,                 DefaultFont, DisabledColor, DummyAction>,
        makeComponent<MenuItem, BluetoothIsReadyText,                   DefaultFont, DisabledColor, DummyAction>,
        makeComponent<MenuItem, BluetoothIsReadyMasterText,             DefaultFont, DisabledColor, DummyAction>,
        makeComponent<MenuItem, StaticText<TEXT_BLUETOOTHBEGIN>,        DefaultFont, DisabledColor, BluetoothBeginAction>,
        makeComponent<MenuItem, StaticText<TEXT_BLUETOOTHBEGINMASTER>,  DefaultFont, DisabledColor, BluetoothBeginMasterAction>,
        makeComponent<MenuItem, StaticText<TEXT_BLUETOOTHFLUSH>,        DefaultFont, DisabledColor, BluetoothFlushAction>,
        makeComponent<MenuItem, StaticText<TEXT_BLUETOOTHEND>,          DefaultFont, DisabledColor, BluetoothEndAction>,
        makeComponent<MenuItem, StaticText<TEXT_BLUETOOTHDISCONNECT>,   DefaultFont, DisabledColor, BluetoothDisconnectAction>,
        makeComponent<MenuItem, StaticText<TEXT_BACK>,                  DefaultFont, DefaultColor,              SwitchScreenAction<Tscreen>>
    >
{};
}
