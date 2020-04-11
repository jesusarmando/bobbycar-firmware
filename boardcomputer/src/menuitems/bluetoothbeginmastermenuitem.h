#pragma once

#include <HardwareSerial.h>

#include "menuitem.h"
#include "titleinterface.h"
#include "globals.h"

namespace {
template<const char *Ttext>
class BluetoothBeginMasterMenuItem final : public MenuItem, public StaticTitle<Ttext>
{
public:
    void triggered() override;
};

template<const char *Ttext>
void BluetoothBeginMasterMenuItem<Ttext>::triggered()
{
    if (!bluetoothSerial.begin("bobbyquad", true))
    {
        Serial.println("Could not begin bluetooth master");
        // TODO: better error handling
    }
}
}
