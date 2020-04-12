#pragma once

#include "actioninterface.h"
#include "globals.h"

namespace {
class BluetoothFlushAction : public virtual ActionInterface
{
public:
    void triggered() override
    {
        bluetoothSerial.flush();
    }
};
}
