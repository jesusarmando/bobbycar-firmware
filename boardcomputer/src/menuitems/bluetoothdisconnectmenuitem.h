#pragma once

#include "menuitem.h"
#include "titleinterface.h"
#include "globals.h"

namespace {
template<const char *Ttext>
class BluetoothDisconnectMenuItem final : public MenuItem, public StaticTitle<Ttext>
{
public:
    void triggered() override;
};

template<const char *Ttext>
void BluetoothDisconnectMenuItem<Ttext>::triggered()
{
    if (!bluetoothSerial.disconnect())
    {
        Serial.println("Could not disconnect bluetooth");
        // TODO: better error handling
    }
}
}
