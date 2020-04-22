#pragma once

#include <HardwareSerial.h>

#include "actioninterface.h"
#include "globals.h"

namespace {
class BluetoothConnectBmsAction : public virtual ActionInterface
{
public:
    void triggered() override
    {
        uint8_t remoteAddress[ESP_BD_ADDR_LEN] = {0xAA, 0xBB, 0xCC, 0xA1, 0x23, 0x45};
        if (!bluetoothSerial.connect(remoteAddress))
        {
            Serial.println("Could not connect bluetooth to bms");
            // TODO: better error handling
        }
    }
};
}
