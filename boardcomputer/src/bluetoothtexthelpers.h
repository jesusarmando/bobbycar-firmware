#pragma once

#include "textinterface.h"
#include "globals.h"
#include "utils.h"

namespace {
template<const char *Ttext, typename TreturnType, TreturnType (BluetoothSerial::*Tmethod)()>
using BluetoothStatusTextHelper = StatusTextHelper<Ttext, BluetoothSerial, &bluetoothSerial, TreturnType, Tmethod>;

constexpr char TEXT_BLUETOOTHAVAILABLE[] = "Available: ";
using BluetoothAvailableText = BluetoothStatusTextHelper<TEXT_BLUETOOTHAVAILABLE, int, &BluetoothSerial::available>;

constexpr char TEXT_BLUETOOTHHASCLIENT[] = "Has client: ";
using BluetoothHasClientText = BluetoothStatusTextHelper<TEXT_BLUETOOTHHASCLIENT, bool, &BluetoothSerial::hasClient>;

//constexpr char TEXT_BLUETOOTHCONNECTED[] = "Connected: ";
//using BluetoothConnectedText = BluetoothStatusTextHelper<TEXT_BLUETOOTHCONNECTED, bool, &BluetoothSerial::connected>;
struct BluetoothConnectedText : public virtual TextInterface {
public:
    String text() const override { return String{"connected: "} + toString(bluetoothSerial.connected()); }
};

//constexpr char TEXT_BLUETOOTHISREADY[] = "Is ready: ";
//using BluetoothIsReadyText = BluetoothStatusTextHelper<TEXT_BLUETOOTHISREADY, bool, &BluetoothSerial::isReady>;
struct BluetoothIsReadyText : public virtual TextInterface {
public:
    String text() const override { return String{"isReady: "} + toString(bluetoothSerial.isReady()); }
};

//constexpr char TEXT_BLUETOOTHISREADYMASTER[] = "Is ready (M): ";
//using BluetoothIsReadyMasterText = BluetoothStatusTextHelper<TEXT_BLUETOOTHISREADYMASTER, bool, &BluetoothSerial::isReady>;
class BluetoothIsReadyMasterText : public virtual TextInterface {
public:
    String text() const override { return String{"isReady (M): "} + toString(bluetoothSerial.isReady(true)); }
};
}
