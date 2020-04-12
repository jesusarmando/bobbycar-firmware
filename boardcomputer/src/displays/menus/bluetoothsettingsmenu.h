#pragma once

#include "staticmenudisplay.h"
#include "menuitems/livestatusmenuitem.h"
#include "menuitems/bluetoothbeginmenuitem.h"
#include "menuitems/bluetoothbeginmastermenuitem.h"
#include "menuitems/bluetoothflushmenuitem.h"
#include "menuitems/bluetoothendmenuitem.h"
#include "menuitems/bluetoothdisconnectmenuitem.h"
#include "menuitems/backmenuitem.h"
#include "globals.h"
#include "texts.h"

namespace {
struct BluetoothAvailableLiveStatus { static String getText() { return String{"available: "} + bluetoothSerial.available(); } };
struct BluetoothHasClientLiveStatus { static String getText() { return String{"hasClient: "} + (bluetoothSerial.hasClient() ? "true" : "false"); } };
//struct BluetoothConnectedLiveStatus { static String getText() { return String{"connected: "} + (bluetoothSerial.connected() ? "true" : "false"); } };
struct BluetoothIsReadyLiveStatus { static String getText() { return String{"isReady: "} + (bluetoothSerial.isReady() ? "true" : "false"); } };
struct BluetoothIsReadyMasterLiveStatus { static String getText() { return String{"isReady (M): "} + (bluetoothSerial.isReady(true) ? "true" : "false"); } };

template<typename Tscreen>
class BluetoothSettingsMenu final :
    public StaticTitle<TEXT_BLUETOOTHSETTINGS>,
    public StaticMenuDisplay<
        LiveStatusMenuItem<BluetoothAvailableLiveStatus>,
        LiveStatusMenuItem<BluetoothHasClientLiveStatus>,
//        LiveStatusMenuItem<BluetoothConnectedLiveStatus>,
        LiveStatusMenuItem<BluetoothIsReadyLiveStatus>,
        LiveStatusMenuItem<BluetoothIsReadyMasterLiveStatus>,
        BluetoothBeginMenuItem,
        BluetoothBeginMasterMenuItem,
        BluetoothFlushMenuItem,
        BluetoothEndMenuItem,
        BluetoothDisconnectMenuItem,
        BackMenuItem<Tscreen>
    >
{};
}
