#pragma once

#include <HardwareSerial.h>

#include "menuitems/menuitem.h"
#include "titleinterface.h"
#include "texts.h"
#include "globals.h"

namespace {
class BluetoothBeginMasterMenuItem final : public MenuItem, public StaticTitle<TEXT_BLUETOOTHBEGINMASTER>
{
public:
    void triggered() override;
};

void BluetoothBeginMasterMenuItem::triggered()
{
    if (!bluetoothSerial.begin("bobbyquad", true))
    {
        Serial.println("Could not begin bluetooth master");
        // TODO: better error handling
    }
}
}
