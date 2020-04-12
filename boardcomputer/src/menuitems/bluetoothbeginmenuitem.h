#pragma once

#include "menuitems/menuitem.h"
#include "titleinterface.h"
#include "texts.h"
#include "globals.h"

namespace {
class BluetoothBeginMenuItem final : public MenuItem, public StaticTitle<TEXT_BLUETOOTHBEGIN>
{
public:
    void triggered() override;
};

void BluetoothBeginMenuItem::triggered()
{
    if (!bluetoothSerial.begin("bobbyquad"))
    {
        Serial.println("Could not begin bluetooth");
        // TODO: better error handling
    }
}
}
