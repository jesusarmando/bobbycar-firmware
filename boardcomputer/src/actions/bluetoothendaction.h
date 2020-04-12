#pragma once

#include "actioninterface.h"
#include "globals.h"

namespace {
class BluetoothEndAction : public virtual ActionInterface
{
public:
    void triggered() override
    {
        bluetoothSerial.end();
    }
};
}
