#pragma once

#include <HardwareSerial.h>
#include <WiFi.h>

#include "actioninterface.h"

namespace {
class WifiEnableIpV6Action : public virtual ActionInterface
{
public:
    void triggered() override
    {
        if (!WiFi.enableIpV6())
        {
            Serial.println("Could not enableIpV6 WiFi");
            // TODO: better error handling
        }
    }
};
}
