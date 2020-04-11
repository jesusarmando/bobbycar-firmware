#pragma once

#include <WiFi.h>

#include "menuitem.h"

namespace {
template<const char *Ttext>
class WifiSoftApEnableIpV6MenuItem final : public MenuItem, public StaticTitle<Ttext>
{
public:
    void triggered() override;
};

template<const char *Ttext>
void WifiSoftApEnableIpV6MenuItem<Ttext>::triggered()
{
    if (!WiFi.softAPenableIpV6())
    {
        Serial.println("Could not softAPenableIpV6 WiFi");
        // TODO: better error handling
    }
}
}
