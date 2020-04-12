#pragma once

#include <HardwareSerial.h>

#include "actioninterface.h"
#include "globals.h"

namespace {
class BluetoothBeginMasterAction : public virtual ActionInterface
{
public:
    void triggered() override
    {
        if (!bluetoothSerial.begin("bobbyquad", true))
        {
            Serial.println("Could not begin bluetooth master");
            // TODO: better error handling
        }
    }
};
}
