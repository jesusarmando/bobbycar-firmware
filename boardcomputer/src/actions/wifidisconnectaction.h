#pragma once

#include <HardwareSerial.h>
#include <WiFi.h>

#include "actioninterface.h"

namespace {
class WifiDisconnectAction : public virtual ActionInterface
{
public:
    void triggered() override
    {
        if (!WiFi.disconnect())
        {
            Serial.println("Could not disconnect WiFi");
            // TODO: better error handling
        }
    }
};
}
