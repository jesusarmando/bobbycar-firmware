#pragma once

#include <HardwareSerial.h>

#include "actioninterface.h"
#include "globals.h"

namespace {
class BluetoothBeginAction : public virtual ActionInterface
{
public:
    void triggered() override
    {
        if (!bluetoothSerial.begin("bobbyquad"))
        {
            Serial.println("Could not begin bluetooth");
            // TODO: better error handling
        }
    }
};
}
