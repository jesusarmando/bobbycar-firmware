#pragma once

#include <HardwareSerial.h>

#include "actioninterface.h"
#include "globals.h"

namespace {
class BluetoothDisconnectAction : public virtual ActionInterface
{
public:
    void triggered() override
    {
        if (!bluetoothSerial.disconnect())
        {
            Serial.println("Could not disconnect bluetooth");
            // TODO: better error handling
        }
    }
};
}
