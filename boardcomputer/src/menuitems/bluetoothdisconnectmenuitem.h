#pragma once

#include "menuitems/menuitem.h"
#include "titleinterface.h"
#include "texts.h"
#include "globals.h"

namespace {
class BluetoothDisconnectMenuItem final : public MenuItem, public StaticTitle<TEXT_BLUETOOTHDISCONNECT>
{
public:
    void triggered() override;
};

void BluetoothDisconnectMenuItem::triggered()
{
    if (!bluetoothSerial.disconnect())
    {
        Serial.println("Could not disconnect bluetooth");
        // TODO: better error handling
    }
}
}
